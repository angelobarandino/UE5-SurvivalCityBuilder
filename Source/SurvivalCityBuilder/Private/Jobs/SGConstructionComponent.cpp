// Fill out your copyright notice in the Description page of Project Settings.


#include "Jobs/SGConstructionComponent.h"
#include "Inventory/SGInventoryComponent.h"

// Sets default values for this component's properties
USGConstructionComponent::USGConstructionComponent()
{
	JobProfession = EProfession::Builder;
}

bool USGConstructionComponent::ValidateCanTakeJob(FGuid OwnerId)
{
	if (USGInventoryComponent* InventoryComp = GetInventoryComponent())
	{
		TArray<TEnumAsByte<EResourceType>> ResourceTypes;
		InventoryComp->GetResourceTypesInStorage(ResourceTypes);

		for (const EResourceType ResourceType : ResourceTypes)
		{
			FSGResourceItem ResourceItem;
			if (InventoryComp->TryGetResource(ResourceType, ResourceItem))
			{
				if (ResourceItem.Quantity < ResourceItem.MinQuantity)
				{
					return false;
				}
			}
		}
	}

	return true;
}

// Called when the game starts
void USGConstructionComponent::BeginPlay()
{
	Super::BeginPlay();
}