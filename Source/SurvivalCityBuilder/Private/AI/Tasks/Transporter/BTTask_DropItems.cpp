// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/Transporter/BTTask_DropItems.h"
#include "Inventory/SGInventoryComponent.h"
#include "Jobs/SGTransporterComponent.h"
#include <Core/GameplayHelpers.h>

EBTNodeResult::Type UBTTask_DropItems::ReceivedExecute(FSGTaskData& TaskData)
{
	USGTransporterComponent* TransportComp = TaskData.OwnerAI->GetJobComponent<USGTransporterComponent>();
	if (TransportComp == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBTTask_DropItems: OwnerAI (%s) failed to execute job. No `USGTransporterComponent` job component"));
		return EBTNodeResult::Failed;
	}

	if (const FPickupItem* PickupItem = TransportComp->GetAssignedPickupItem(TaskData.OwnerAIGuid))
	{
		if (USGInventoryComponent* TargetStorage = TransportComp->GetInventoryComponent())
		{
			if (TargetStorage->AddQuantity(PickupItem->ResourceType, PickupItem->PickupQuantity))
			{
				TransportComp->ValidateResourceRequirements();

				return EBTNodeResult::Succeeded;
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("UBTTask_DropItems: An OwnerAI has failed adding items to storage."));
	return EBTNodeResult::Failed;
}
