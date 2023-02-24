// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_SGBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/SGAIController.h"

EBTNodeResult::Type UBTTask_SGBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASGAIController* OwnerAI = Cast<ASGAIController>(OwnerComp.GetOwner());
	if (OwnerAI == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBTTask_SGBase: OwnerAI (%s) failed to execute."));

		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBTTask_SGBase: OwnerAI (%s) failed to execute. No blackboard component setup."));

		return EBTNodeResult::Failed;
	}

	FSGTaskData TaskData = FSGTaskData();
	TaskData.BehaviorTreeComp = &OwnerComp;
	TaskData.BlackboardComp = BlackboardComp;
	TaskData.OwnerAIGuid = OwnerAI->ControllerGuid;
	TaskData.OwnerAI = OwnerAI;
	return ReceivedExecute(TaskData);
}
