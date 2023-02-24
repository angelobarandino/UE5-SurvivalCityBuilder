// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/Transporter/BTTask_SetDropLocation.h"
#include "Inventory/SGInventoryComponent.h"
#include "Jobs/SGTransporterComponent.h"

EBTNodeResult::Type UBTTask_SetDropLocation::ReceivedExecute(FSGTaskData& TaskData)
{
	USGTransporterComponent* TransportComp = TaskData.OwnerAI->GetJobComponent<USGTransporterComponent>();
	if (TransportComp == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UBTTask_SetDropLocation: OwnerAI (%s) failed to execute job. No `USGTransporterComponent` job component"));
		return EBTNodeResult::Failed;
	}

	FVector PickupLocation = TransportComp->GetOwner()->GetActorLocation();
	TaskData.BlackboardComp->SetValueAsVector(Location.SelectedKeyName, PickupLocation);
	return EBTNodeResult::Succeeded;
}
