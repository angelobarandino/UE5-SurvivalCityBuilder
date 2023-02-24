// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_SearchJob.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCITYBUILDER_API UBTService_SearchJob : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_SearchJob();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
