// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGGameplayTypes.h"
#include "Components/ActorComponent.h"
#include "Inventory/SGInventory.h"
#include "SGInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALCITYBUILDER_API USGInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USGInventoryComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Resource Item")
	TEnumAsByte<EResourceStorageRule> StorageRule = EResourceStorageRule::Both;

	UPROPERTY(EditAnywhere, Category = "Resource Inventory")
	TMap<TEnumAsByte<EResourceType>, FSGResourceItem> LocalResourceStorage;
	
	UFUNCTION(BlueprintCallable, Category = "Resource Inventory")
	void AddResource(FSGResourceItem ResourceItem);

	UFUNCTION(BlueprintCallable, Category = "Resource Inventory")
	bool TryGetResource(const EResourceType ResourceType, FSGResourceItem& ResourceItem);

	UFUNCTION(BlueprintCallable, Category = "Resource Inventory")
	bool AddQuantity(const EResourceType ResourceType, const int32 AddQuantity);

	UFUNCTION(BlueprintCallable, Category = "Resource Inventory")
	bool RemoveQuantity(const EResourceType ResourceType, const int32 GetQuantity);

	UFUNCTION(BlueprintCallable, Category = "Resource Inventory")
	bool ContainsResource(const EResourceType ResourceType, int32& CurrentQuantity);

	UFUNCTION(BlueprintCallable, Category = "Resource Inventory")
	void GetResourceTypesInStorage(TArray<TEnumAsByte<EResourceType>>& ResourceTypes);

	UFUNCTION(BlueprintCallable, Category = "Resource Inventory")
	bool HasRequiredQuantity(const EResourceType ResourceType);


	UFUNCTION(BlueprintCallable, Category = "Resource Inventory")
	FORCEINLINE FVector GetStorageLocation()
	{
		return GetOwner()->GetActorLocation();
	}

	UFUNCTION(BlueprintCallable, Category = "Resource Inventory")
	FORCEINLINE void Destroy()
	{
		LocalResourceStorage.Empty();
		DestroyComponent();
	}
};
