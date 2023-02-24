// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Jobs/SGJobBaseComponent.h"
#include "Jobs/SGJobComponentInterface.h"
#include "SGJobPortalComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnJobPostCreated, ISGJobInterface*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnJobPostRemoved, ISGJobInterface*);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALCITYBUILDER_API USGJobPortalComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	TMap<FGuid, class ISGJobInterface*> AvailableJobs;

public:
	USGJobPortalComponent();

	FOnJobPostCreated OnJobPostCreated;
	FOnJobPostRemoved OnJobPostRemoved;

	virtual void BeginPlay() override;

	void CreateJobPost(ISGJobInterface* JobComponent);
	void RemoveJobPost(ISGJobInterface* JobComponent);

	ISGJobInterface* SearchJobByProfession(const enum EProfession Profession);
	ISGJobInterface* SearchJobByClass(TSubclassOf<class USGJobBaseComponent> JobComponentClass);

	UFUNCTION(BlueprintPure)
	FORCEINLINE TArray<USGJobBaseComponent*> GetAvailableJobs()
	{
		TArray<FGuid> GuidKeys;
		AvailableJobs.GetKeys(GuidKeys);

		TArray<USGJobBaseComponent*> Jobs;
		for (const FGuid Key : GuidKeys)
		{
			Jobs.Add(Cast<USGJobBaseComponent>(*AvailableJobs.Find(Key)));
		}

		return Jobs;
	}
};
