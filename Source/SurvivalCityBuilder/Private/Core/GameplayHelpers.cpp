// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameplayHelpers.h"
#include "AI/SGAIController.h"
#include "SGGameplayTypes.h"
#include "Buildings/SGBuildingActor.h"
#include "Jobs/SGJobPortalComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "World/SGGameState.h"
#include "Engine/World.h"
#include "EngineUtils.h"

void UGameplayHelpers::CreateJobPost(const UWorld* World, ISGJobInterface* JobComponent)
{
	if (ASGGameState* GameState = Cast<ASGGameState>(World->GetGameState()))
	{
		if (USGJobPortalComponent* JobPortal = GameState->GetJobPortalComponent())
		{
			JobPortal->CreateJobPost(JobComponent);
		}
	}
}

void UGameplayHelpers::RemoveJobPost(const UWorld* World, ISGJobInterface* JobComponent)
{
	if (ASGGameState* GameState = Cast<ASGGameState>(World->GetGameState()))
	{
		if (USGJobPortalComponent* JobPortal = GameState->GetJobPortalComponent())
		{
			JobPortal->RemoveJobPost(JobComponent);
		}
	}
}


FJobSearchResult UGameplayHelpers::SearchJobByProfession(const UWorld* World, const EProfession Profession)
{
	FJobSearchResult SearchResult;

	if (World)
	{
		if (ASGGameState* GameState = Cast<ASGGameState>(World->GetGameState()))
		{
			if (USGJobPortalComponent* JobPortal = GameState->GetJobPortalComponent())
			{
				if (ISGJobInterface* JobComponent = JobPortal->SearchJobByProfession(Profession))
				{
					SearchResult.HasResult = true;
					SearchResult.Key = JobComponent->GetJobKey();
					SearchResult.Location = JobComponent->GetJobLocation();
					SearchResult.Owner = JobComponent->GetOwnerBuilding();
					SearchResult.Job = Cast<USGJobBaseComponent>(JobComponent);
				}
			}
		}
	}

	return SearchResult;
}

FJobSearchResult UGameplayHelpers::SearchJobByClass(const UWorld* World, TSubclassOf<USGJobBaseComponent> JobComponentClass)
{
	FJobSearchResult SearchResult;

	if (World)
	{
		if (ASGGameState* GameState = Cast<ASGGameState>(World->GetGameState()))
		{
			if (USGJobPortalComponent* JobPortal = GameState->GetJobPortalComponent())
			{
				if (ISGJobInterface* JobComponent = JobPortal->SearchJobByClass(JobComponentClass))
				{
					SearchResult.HasResult = true;
					SearchResult.Key = JobComponent->GetJobKey();
					SearchResult.Location = JobComponent->GetJobLocation();
					SearchResult.Owner = JobComponent->GetOwnerBuilding();
					SearchResult.Job = Cast<USGJobBaseComponent>(JobComponent);
				}
			}
		}
	}

	return SearchResult;
}

FJobSearchResult UGameplayHelpers::SearchJobByProfession(const AActor* Actor, const EProfession Profession)
{
	return SearchJobByProfession(Actor->GetWorld(), Profession);
}

FJobSearchResult UGameplayHelpers::SearchJobByClass(const AActor* Actor, TSubclassOf<USGJobBaseComponent> JobComponentClass)
{
	return SearchJobByClass(Actor->GetWorld(), JobComponentClass);
}

ASGBuildingActor* UGameplayHelpers::FindNearestBuildingWithComponentOfType(const AActor* ActorOrigin, TSubclassOf<UActorComponent> ComponentClass)
{
	if (ActorOrigin == nullptr)
	{
		return nullptr;
	}

	// Get character location
	FVector Origin = ActorOrigin->GetActorLocation();

	// Intialize local variables
	ASGBuildingActor* NearestActor = nullptr;
	float DistanceFromNearestActor = TNumericLimits<float>::Max();

	// Iterate to all building and get the nearest by filtering the build type
	TArray<ASGBuildingActor*> ActorsToCheck;
	for (TActorIterator<ASGBuildingActor> ActorToCheckItr(ActorOrigin->GetWorld()); ActorToCheckItr; ++ActorToCheckItr)
	{
		// calculte the distance from our AI location to building location
		const FVector BuildingLocation = ActorToCheckItr->GetActorLocation();
		const float DistanceFromActorToCheck = (Origin - BuildingLocation).SizeSquared();

		// check if distance from previous building is smaller
		if (DistanceFromActorToCheck < DistanceFromNearestActor)
		{
			DistanceFromNearestActor = DistanceFromActorToCheck;

			// assign our new nearest building
			NearestActor = *ActorToCheckItr;
		}
	}

	return NearestActor;
}

FName UGameplayHelpers::GetResourceTypeNameFromValue(const int32 EnumValue)
{
	UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *FString("EResourceType"));
	return EnumPtr->GetNameByValue(EnumValue);
}

EResourceType UGameplayHelpers::GetResourceTypeValueFromName(const FName EnumName)
{
	UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *FString("EResourceType"));
	return static_cast<EResourceType>(EnumPtr->GetValueByName(EnumName));
}

ASGAIController* UGameplayHelpers::GetCharacterByOwnerId(const UWorld* World, const FGuid OwnerGuid)
{
	if (World)
	{
		if (ASGGameState* GameState = Cast<ASGGameState>(World->GetGameState()))
		{
			return GameState->GetCharacterByOwnerId(OwnerGuid);
		}
	}

	return nullptr;
}
