// Fill out your copyright notice in the Description page of Project Settings.


#include "Jobs/SGTransporterComponent.h"
#include "AI/SGAI.h"
#include "Buildings/SGBuildingActor.h"
#include "Core/GameplayHelpers.h"
#include "Inventory/SGInventoryComponent.h"
#include "SGGameplayTypes.h"
#include "EngineUtils.h"

USGTransporterComponent::USGTransporterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	JobProfession = EProfession::Transporter;
	SetMaxJobSlots(2);
}

void USGTransporterComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool USGTransporterComponent::ValidateCanTakeJob(const FGuid OwnerGuid)
{
	if (TransportReason == ETransportReason::FillMaxQuantity)
	{
		return true;
	}

	if (TransportReason == ETransportReason::FillMinQuantity)
	{
		// find the character who pickup this transport job
		if (ASGAIController* Controller = UGameplayHelpers::GetCharacterByOwnerId(GetWorld(), OwnerGuid))
		{
			// cache and get the number of items the worker can carry
			const int32 CarryCapacity = Controller->GetCharacter()->GetCarryCapacity();

			if (USGInventoryComponent* OwnerInventoryComp = GetInventoryComponent())
			{
				// loop through all the resources required for this transport job
				OwnerInventoryComp->GetResourceTypesInStorage(ResourceTypesForTransport);
				for (const EResourceType ResourceType : ResourceTypesForTransport)
				{
					FSGResourceItem ResourceItem;
					if (!GetInventoryComponent()->TryGetResource(ResourceType, ResourceItem))
					{
						continue;
					}

					// Find nearest storage that contains the resource type to pickup
					USGInventoryComponent* PickupStorage = FindNearestStorage(ResourceType);
					if (PickupStorage == nullptr)
					{
						continue;
					}

					// lets get all the workers who had already take this job
					// and then calculate the remaining items to pickup for the new worker
					int32 TotalPickupItems = ResourceItem.Quantity;
					for (const auto& OngoingPickupData : OngoingPickups)
					{
						if (const FPickupItem* OngoingPickup = &OngoingPickupData.Value)
						{
							if (OngoingPickup->ResourceType == ResourceType)
							{
								TotalPickupItems += OngoingPickup->PickupQuantity;
							}
						}
					}

					// if there's enough workers who took this job, then
					const int32 ItemsLeftToPickup = ResourceItem.MinQuantity - TotalPickupItems;
					if (ItemsLeftToPickup <= 0)
					{
						continue;
					}

					// calculate the amount if items the new worker can pickup based max items he can carry.
					const int32 ItemsToPickup = FMath::Clamp(CarryCapacity, 0, ItemsLeftToPickup);
					if (ItemsToPickup > 0)
					{
						// assign this worker to this job
						OngoingPickups.Add(Controller->ControllerGuid, FPickupItem(ResourceType, ItemsToPickup, PickupStorage));
						return true;
					}
				}
			}
		}
	}
	
	return false;
}

void USGTransporterComponent::LeaveJobSlot(const FGuid OwnerGuid)
{
	OngoingPickups.Remove(OwnerGuid);

	Super::LeaveJobSlot(OwnerGuid);
}

void USGTransporterComponent::ValidateResourceRequirements()
{
	if (USGInventoryComponent* OwnerInventoryComp = GetInventoryComponent())
	{
		// if this tranport job is for building construction,
		// then we check if all required resource has been fulfilled.
		if (TransportReason == ETransportReason::FillMinQuantity)
		{
			bool bIsRequirementsFulfilled = true;

			//OwnerInventoryComp->GetResourceTypesInStorage(ResourceTypesForTransport);
			for (const EResourceType ResourceType : ResourceTypesForTransport)
			{
				if (!OwnerInventoryComp->HasRequiredQuantity(ResourceType))
				{
					bIsRequirementsFulfilled = false;
					break;
				}
			}

			if (bIsRequirementsFulfilled)
			{
				bCanStartJob = false;
				//UGameplayHelpers::RemoveJobPost(GetWorld(), this);

				UE_LOG(LogTemp, Warning, TEXT("FULFILLED (%s)"), *JobKey.ToString());
				DestroyComponent();
			}
			else 
			{
				bCanStartJob = true;
			}
		}
	}
}

USGInventoryComponent* USGTransporterComponent::FindNearestStorage(EResourceType ResourceType)
{
	USGInventoryComponent* OwnerInventoryComp = GetInventoryComponent();
	if (OwnerInventoryComp == nullptr)
	{
		return nullptr;
	}

	USGInventoryComponent* NearestInventoryComp = nullptr;
	FVector OriginLocation = GetOwner()->GetActorLocation();
	
	TSubclassOf<USGInventoryComponent> InventoryComponentClass = USGInventoryComponent::StaticClass();
	float DistanceFromNearestInventoryComp = TNumericLimits<float>::Max();
	
	for (TActorIterator<ASGBuildingActor> BuildingActorItr(GetWorld()); BuildingActorItr; ++BuildingActorItr)
	{
		// skip if its the current job owner
		if (*BuildingActorItr == OwnerInventoryComp->GetOwner())
		{
			continue;
		}

		// check if it has the inventory component
		if (USGInventoryComponent* TargetInventoryComp = Cast<USGInventoryComponent>(BuildingActorItr->GetComponentByClass(InventoryComponentClass)))
		{
			if (TargetInventoryComp->StorageRule == EResourceStorageRule::InOnly)
			{
				continue;
			}

			int32 CurrentQuantity;
			// if it has the resource we are searching and not emptied
			if (TargetInventoryComp->ContainsResource(ResourceType, CurrentQuantity))
			{
				if (CurrentQuantity == 0)
				{
					continue;
				}

				// get the target location
				const FVector TargetLocation = OwnerInventoryComp->GetOwner()->GetActorLocation();
				const float DistanceFromActorToCheck = (OriginLocation - TargetLocation).SizeSquared();

				// check if the distance is smaller than the last storage we checked!
				if (DistanceFromActorToCheck < DistanceFromNearestInventoryComp)
				{
					DistanceFromNearestInventoryComp = DistanceFromActorToCheck;
					NearestInventoryComp = TargetInventoryComp;
				}
			}
		}
	}

	return NearestInventoryComp;
}

void USGTransporterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
