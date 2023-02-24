// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Tasks/BTTask_SGBase.h"
#include "BTTask_PickupItems.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCITYBUILDER_API UBTTask_PickupItems : public UBTTask_SGBase
{
	GENERATED_BODY()
	
protected:

	virtual EBTNodeResult::Type ReceivedExecute(FSGTaskData& TaskData) final override;
};
