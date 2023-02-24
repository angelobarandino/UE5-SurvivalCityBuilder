// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/Transporter/BTTask_PickupItems.h"
#include "Inventory/SGInventoryComponent.h"
#include "Jobs/SGTransporterComponent.h"

EBTNodeResult::Type UBTTask_PickupItems::ReceivedExecute(FSGTaskData& TaskData)
{
	USGTransporterComponent* TransportComp = TaskData.OwnerAI->GetJobComponent<USGTransporterComponent>();
	if (TransportComp == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBTTask_PickupItems: OwnerAI (%s) failed to execute job. No `USGTransporterComponent` job component"));

		return EBTNodeResult::Failed;
	}

	bool bResult = false;
	if (const FPickupItem* PickupItem = TransportComp->GetAssignedPickupItem(TaskData.OwnerAIGuid))
	{
		if (USGInventoryComponent* TargetStorage = PickupItem->PickupStorage)
		{
			bResult = TargetStorage->RemoveQuantity(
				PickupItem->ResourceType, 
				PickupItem->PickupQuantity);
		}
	}
	
	return bResult ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
