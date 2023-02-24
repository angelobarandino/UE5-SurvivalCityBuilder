// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/SGInventoryComponent.h"

// Sets default values for this component's properties
USGInventoryComponent::USGInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USGInventoryComponent::AddResource(FSGResourceItem ResourceItem)
{
	if (LocalResourceStorage.Contains(ResourceItem.ResourceAsset->Type))
	{
		return;
	}

	LocalResourceStorage.Add(ResourceItem.ResourceAsset->Type, ResourceItem);
}

bool USGInventoryComponent::TryGetResource(const EResourceType ResourceType, FSGResourceItem& ResourceItem)
{
	if (const FSGResourceItem* FoundResourceItem = LocalResourceStorage.Find(ResourceType))
	{
		ResourceItem = *FoundResourceItem;
		return true;
	}

	return false;
}

bool USGInventoryComponent::AddQuantity(const EResourceType ResourceType, const int32 AddQuantity)
{
	if (FSGResourceItem* ResourceItem = LocalResourceStorage.Find(ResourceType))
	{
		UE_LOG(LogTemp, Display, TEXT("USGInventoryComponent::AddQuantity(%d,%d): CurQty=%d | MinQty=%d | MaxQty=%d"),
			ResourceType,
			AddQuantity,
			ResourceItem->Quantity,
			ResourceItem->MinQuantity,
			ResourceItem->MaxQuantity);

		const int32 NewQuantity = ResourceItem->Quantity + AddQuantity;
		
		if (ResourceItem->MaxQuantity >= NewQuantity)
		{
			ResourceItem->Quantity = NewQuantity;

			UE_LOG(LogTemp, Display, TEXT("USGInventoryComponent::AddQuantity Result: AddQty=%d | NewQty=%d"), AddQuantity, ResourceItem->Quantity);
			return true;
		}
	}

	UE_LOG(LogTemp, Display, TEXT("USGInventoryComponent::AddQuantity Result: FAILED!!! Type=%d | AddQty=%d"), ResourceType, AddQuantity);

	return false;
}

bool USGInventoryComponent::RemoveQuantity(const EResourceType ResourceType, const int32 GetQuantity)
{
	if (FSGResourceItem* ResourceItem = LocalResourceStorage.Find(ResourceType))
	{
		UE_LOG(LogTemp, Display, TEXT("USGInventoryComponent::RemoveQuantity(%d,%d): CurQty=%d | MinQty=%d | MaxQty=%d"),
			ResourceType,
			GetQuantity,
			ResourceItem->Quantity,
			ResourceItem->MinQuantity,
			ResourceItem->MaxQuantity);

		if (ResourceItem->Quantity != 0)
		{
			ResourceItem->Quantity = FMath::Clamp(
				ResourceItem->Quantity - GetQuantity, 
				0, 
				ResourceItem->MaxQuantity
			);

			UE_LOG(LogTemp, Display, TEXT("USGInventoryComponent::RemoveQuantity Result: GetQty=%d | NewQty=%d"), GetQuantity, ResourceItem->Quantity);
			return true;
		}
	}

	return false;
}

bool USGInventoryComponent::ContainsResource(const EResourceType ResourceType, int32& CurrentQuantity)
{
	if (const FSGResourceItem* ResourceItem = LocalResourceStorage.Find(ResourceType))
	{
		CurrentQuantity = ResourceItem->Quantity;
		return true;
	}

	return false;
}

void USGInventoryComponent::GetResourceTypesInStorage(TArray<TEnumAsByte<EResourceType>>& ResourceTypes)
{
	LocalResourceStorage.GetKeys(ResourceTypes);
}

bool USGInventoryComponent::HasRequiredQuantity(const EResourceType ResourceType)
{
	if (const FSGResourceItem* ResourceItem = LocalResourceStorage.Find(ResourceType))
	{
		return ResourceItem->Quantity >= ResourceItem->MinQuantity;
	}

	return false;
}
