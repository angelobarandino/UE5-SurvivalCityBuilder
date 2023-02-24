// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SearchJobByClass.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCITYBUILDER_API UBTTask_SearchJobByClass : public UBTTaskNode
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, Category = "Task Variables")
	TSubclassOf<class USGJobBaseComponent> JobComponentClass;

	UPROPERTY(EditAnywhere, Category = "Task Variables")
	bool bReplaceCurrentJob = true;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
