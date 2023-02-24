// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_SearchJobByClass.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Core/GameplayHelpers.h"
#include "AI/SGAIController.h"


EBTNodeResult::Type UBTTask_SearchJobByClass::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent())
	{
		FJobSearchResult SearchResult = UGameplayHelpers::SearchJobByClass(OwnerComp.GetWorld(), JobComponentClass);
		if (SearchResult.HasResult)
		{
			if (ASGAIController* Controller = Cast<ASGAIController>(OwnerComp.GetOwner()))
			{
				if (bReplaceCurrentJob)
				{
					Controller->LeaveJob();
				}

				if (Controller->TakeJob(SearchResult.Job))
				{
					return EBTNodeResult::Succeeded;
				}

				UE_LOG(LogTemp, Warning, TEXT("UBTTask_SearchJobByClass: Failed Taking Job: %s"), *JobComponentClass->GetName());
			}
		}
	}

	return EBTNodeResult::Failed;
}
