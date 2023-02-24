// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Services/BTService_SearchJob.h"
#include "AI/SGAIController.h"
#include "Core/GameplayHelpers.h"
#include "Buildings/SGBuildingActor.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_SearchJob::UBTService_SearchJob()
{
	Interval = 2.5f;
	RandomDeviation = 0.5f;
}

void UBTService_SearchJob::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp == nullptr)
	{
		return;
	}

	if (ASGAIController* Controller = Cast<ASGAIController>(OwnerComp.GetOwner()))
	{
		if (Controller->HasJobComponent())
		{
			return;
		}

		FJobSearchResult JobSearchResult = UGameplayHelpers::SearchJobByProfession(GetWorld(), EProfession::Laborer);
		if (JobSearchResult.HasResult)
		{
			Controller->TakeJob(JobSearchResult.Job);
		}
	}
}

