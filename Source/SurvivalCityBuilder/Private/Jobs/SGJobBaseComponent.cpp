// Fill out your copyright notice in the Description page of Project Settings.

#include "Jobs/SGJobBaseComponent.h"
#include "Buildings/SGBuildingActor.h"
#include "Inventory/SGInventory.h"
#include "Inventory/SGInventoryComponent.h"
#include "Core/GameplayHelpers.h"
#include "AI/SGAICharacter.h"

USGJobBaseComponent::USGJobBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USGJobBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		// Generate Job ID
		JobKey = FGuid::NewGuid();

		// Create a Job Post to trigger our AI's
		UGameplayHelpers::CreateJobPost(GetWorld(), this);
	}
}

void USGJobBaseComponent::OnComponentDestroyed(bool DestroyingHierarchy)
{
	if (GetOwner() && !GetOwner()->bIsEditorOnlyActor)
	{
		if (UWorld* World = GetOwner()->GetWorld())
		{
			// Remove job
			UGameplayHelpers::RemoveJobPost(World, this);
		}
	}

	Super::OnComponentDestroyed(DestroyingHierarchy);
}

FString USGJobBaseComponent::GetJobName()
{
	return *GetFName().ToString();
}

void USGJobBaseComponent::SetMaxJobSlots(const int32 MaxJobSlots)
{
	MaxJobSlotsCanTake = MaxJobSlots;
}

USGInventoryComponent* USGJobBaseComponent::GetInventoryComponent()
{
	if (CurrentInventoryComp == nullptr)
	{
		if (UActorComponent* ActorComp = GetOwner()->GetComponentByClass(USGInventoryComponent::StaticClass()))
		{
			CurrentInventoryComp = Cast<USGInventoryComponent>(ActorComp);
		}
	}

	return CurrentInventoryComp;
}

FGuid USGJobBaseComponent::GetJobKey()
{
	return JobKey;
}

TEnumAsByte<EProfession> USGJobBaseComponent::GetProfession()
{
	return JobProfession;
}

FVector USGJobBaseComponent::GetJobLocation()
{
	return GetOwner()->GetActorLocation();
}

ASGBuildingActor* USGJobBaseComponent::GetOwnerBuilding()
{
	return Cast<ASGBuildingActor>(GetOwner());
}

bool USGJobBaseComponent::HasJobSlot()
{
	if (MaxJobSlotsCanTake == 0)
	{
		return true;
	}

	return JobSlotOwnerKeys.Num() != MaxJobSlotsCanTake;
}

bool USGJobBaseComponent::ValidateCanTakeJob(const FGuid OwnerGuid)
{
	return true;
}

bool USGJobBaseComponent::TakeJobSlot(const FGuid OwnerGuid)
{
	if (ValidateCanTakeJob(OwnerGuid))
	{
		if (MaxJobSlotsCanTake == 0)
		{
			JobSlotOwnerKeys.Add(OwnerGuid);
			return true;
		}

		if (MaxJobSlotsCanTake > JobSlotOwnerKeys.Num())
		{
			JobSlotOwnerKeys.Add(OwnerGuid);
			return true;
		}
	}

	return false;
}

void USGJobBaseComponent::LeaveJobSlot(const FGuid OwnerGuid)
{
	JobSlotOwnerKeys.Remove(OwnerGuid);
}

bool USGJobBaseComponent::CanStartJobTask()
{
	return true;
}

bool USGJobBaseComponent::DoJobTask(const float IncrementAmount)
{
	return false;
}
