// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckProfession.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCITYBUILDER_API UBTDecorator_CheckProfession : public UBTDecorator
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Task Variables")
	TEnumAsByte<enum EProfession> Profession;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};
