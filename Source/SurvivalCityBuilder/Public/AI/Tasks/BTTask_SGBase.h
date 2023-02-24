// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/SGAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SGBase.generated.h"

USTRUCT()
struct FSGTaskData
{
	GENERATED_BODY()

public:
	FSGTaskData() :
		BehaviorTreeComp(nullptr),
		BlackboardComp(nullptr),
		OwnerAI(nullptr),
		OwnerAIGuid(FGuid::FGuid())
	{}

	UBehaviorTreeComponent* BehaviorTreeComp;
	UBlackboardComponent* BlackboardComp;
	ASGAIController* OwnerAI;
	FGuid OwnerAIGuid;
};

/**
 * 
 */
UCLASS(Abstract)
class SURVIVALCITYBUILDER_API UBTTask_SGBase : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) final override;

protected:
	FORCEINLINE virtual EBTNodeResult::Type ReceivedExecute(FSGTaskData& TaskData)
	{
		return EBTNodeResult::Succeeded;
	}
};
