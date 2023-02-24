// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/Transporter/BTTask_SetPickupLocation.h"
#include "Inventory/SGInventoryComponent.h"
#include "Jobs/SGTransporterComponent.h"

EBTNodeResult::Type UBTTask_SetPickupLocation::ReceivedExecute(FSGTaskData& TaskData)
{
	USGTransporterComponent* TransportComp = TaskData.OwnerAI->GetJobComponent<USGTransporterComponent>();
	if (TransportComp == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBTTask_SetPickupLocation: OwnerAI (%s) failed to execute job. No `USGTransporterComponent` job component"));
		
		return EBTNodeResult::Failed;
	}

	if (const FPickupItem* PickupItem = TransportComp->GetAssignedPickupItem(TaskData.OwnerAIGuid))
	{
		FVector PickupLocation = PickupItem->PickupStorage->GetStorageLocation();
		TaskData.BlackboardComp->SetValueAsVector(Location.SelectedKeyName, PickupLocation);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
