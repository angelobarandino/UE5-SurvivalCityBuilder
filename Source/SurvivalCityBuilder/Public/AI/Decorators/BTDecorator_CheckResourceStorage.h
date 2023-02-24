// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckResourceStorage.generated.h"

UENUM(BlueprintType)
enum EQuantityCondition
{
	NotEmpty		= 0 UMETA(DisplayName = "Not Empty"),
	NotUnderMinQty	= 1 UMETA(DisplayName = "Not Under Min Quantity"),
};

/**
 * 
 */
UCLASS()
class SURVIVALCITYBUILDER_API UBTDecorator_CheckResourceStorage : public UBTDecorator
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Task Variables")
	FBlackboardKeySelector StorageKey;

	UPROPERTY(EditAnywhere, Category = "Task Variables|Check Condition")
	bool bAllResourceInStorage;

	UPROPERTY(EditAnywhere, Category = "Task Variables|Check Condition", meta = (EditCondition = "!bAllResourceInStorage"))
	TEnumAsByte<enum EResourceType> ResourceType;

	UPROPERTY(EditAnywhere, Category = "Task Variables|Check Condition")
	TEnumAsByte<EQuantityCondition> QuantityCheckCondition;

	
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};
