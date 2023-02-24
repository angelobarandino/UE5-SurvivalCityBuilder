// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SGJobComponentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USGJobInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SURVIVALCITYBUILDER_API ISGJobInterface
{
	GENERATED_BODY()

public:
	virtual FGuid GetJobKey() = 0;
	virtual FVector GetJobLocation() = 0;
	virtual TEnumAsByte<enum EProfession> GetProfession() = 0;
 	virtual class ASGBuildingActor* GetOwnerBuilding() = 0;

	virtual bool HasJobSlot() = 0;
	virtual bool ValidateCanTakeJob(const FGuid OwnerGuid) = 0;
	virtual bool TakeJobSlot(const FGuid OwnerGuid) = 0;
	virtual void LeaveJobSlot(const FGuid OwnerGuid) = 0;
	
	virtual bool CanStartJobTask() = 0;
	virtual bool DoJobTask(const float IncrementAmount) = 0;
};
