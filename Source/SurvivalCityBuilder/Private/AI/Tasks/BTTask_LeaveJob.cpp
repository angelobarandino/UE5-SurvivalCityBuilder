// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_LeaveJob.h"
#include "AI/SGAIController.h"
#include "Core/GameplayHelpers.h"

EBTNodeResult::Type UBTTask_LeaveJob::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent())
	{
		if (ASGAIController* Controller = Cast<ASGAIController>(OwnerComp.GetOwner()))
		{
			Controller->LeaveJob();
		}
	}

	return EBTNodeResult::Succeeded;
}
