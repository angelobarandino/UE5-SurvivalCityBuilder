// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Tasks/BTTask_SGBase.h"
#include "BTTask_SetDropLocation.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCITYBUILDER_API UBTTask_SetDropLocation : public UBTTask_SGBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Task Variables|Blackboard Setter")
	FBlackboardKeySelector Location;

protected:

	virtual EBTNodeResult::Type ReceivedExecute(FSGTaskData& TaskData) final override;
};
