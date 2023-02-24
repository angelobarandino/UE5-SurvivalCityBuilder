// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/SGAIController.h"
#include "AI/SGAICharacter.h"
#include "Buildings/SGBuildingActor.h"
#include "Core/GameplayHelpers.h"
#include "Jobs/SGJobComponentInterface.h"
#include "Jobs/SGJobPortalComponent.h"
#include "World/SGGameState.h"
#include "World/SGGameMode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

void ASGAIController::BeginPlay()
{
	Super::BeginPlay();

	CurrentGameMode = Cast<ASGGameMode>(GetWorld()->GetAuthGameMode());
	check(CurrentGameMode);

	if (ASGGameState* GameState = CurrentGameMode->GetGameState<ASGGameState>())
	{
		if (USGJobPortalComponent* JobPortalComp = GameState->GetJobPortalComponent())
		{
			JobPortalComp->OnJobPostCreated.AddUObject(this, &ASGAIController::OnJobPostCreated);
			JobPortalComp->OnJobPostRemoved.AddUObject(this, &ASGAIController::OnJobPostRemoved);
		}
	}
}

void ASGAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	RunBrain(EProfession::Laborer);
}

void ASGAIController::RunBrain(const EProfession AIProfession)
{
	Profession = AIProfession;
	
	if (UBehaviorTree* Brain = CurrentGameMode->GetBrain(AIProfession))
	{
		RunBehaviorTree(Brain);
		InitBlackboardVariables();
	}
}

bool ASGAIController::TakeJob(ISGJobInterface* JobComponent)
{
	if (CurrentJobComponent == nullptr)
	{
		if (JobComponent->TakeJobSlot(ControllerGuid))
		{
			//CurrentJobKey = Key;
			CurrentJobComponent = JobComponent;

			RunBrain(CurrentJobComponent->GetProfession());
			return true;
		}
	}

	return false;
}

bool ASGAIController::HasJobComponent()
{
	return CurrentJobComponent != nullptr;
}

bool ASGAIController::LeaveJob()
{
	if (CurrentJobComponent != nullptr)
	{
		CurrentJobComponent->LeaveJobSlot(ControllerGuid);
		CurrentJobComponent = nullptr;

		RunBrain(EProfession::Laborer);
		return true;
	}

	return false;
}

void ASGAIController::OnJobPostCreated(ISGJobInterface* JobComponent)
{
	if (JobComponent == nullptr)
	{
		return;
	}

	if (HasJobComponent())
	{
		return;
	}

	if (JobComponent->HasJobSlot())
	{
		TakeJob(JobComponent);
	}
}

void ASGAIController::OnJobPostRemoved(ISGJobInterface* JobComponent)
{
	if (CurrentJobComponent != nullptr && JobComponent != nullptr)
	{
		if (CurrentJobComponent->GetJobKey() == JobComponent->GetJobKey())
		{
			CurrentJobComponent->LeaveJobSlot(ControllerGuid);
			//CurrentJobComponent = nullptr;
			
			RunBrain(EProfession::Laborer);
		}
	}
}

void ASGAIController::InitBlackboardVariables()
{
	if (UBlackboardComponent* BlackboardComp = GetBlackboardComponent())
	{
		if (CurrentJobComponent)
		{
			BlackboardComp->SetValueAsBool(FName("HasJob"), true);
			BlackboardComp->SetValueAsObject(FName("JobComponent"), Cast<UObject>(CurrentJobComponent));
			BlackboardComp->SetValueAsObject(FName("JobOwner"), CurrentJobComponent->GetOwnerBuilding());
			BlackboardComp->SetValueAsVector(FName("JobLocation"), CurrentJobComponent->GetJobLocation());
		}
		else 
		{
			BlackboardComp->SetValueAsBool(FName("HasJob"), false);
			BlackboardComp->SetValueAsObject(FName("JobComponent"), NULL);
			BlackboardComp->SetValueAsObject(FName("JobOwner"), NULL);
			BlackboardComp->SetValueAsVector(FName("JobLocation"), FVector::DownVector);
		}
	}
}
