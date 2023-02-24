// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGJobBaseComponent.h"
#include "SGTransporterComponent.generated.h"

class USGInventoryComponent;

UENUM(BlueprintType)
enum ETransportReason
{
	FillMaxQuantity	= 0,
	FillMinQuantity	= 1,
};

USTRUCT(BlueprintType)
struct FPickupItem
{
	GENERATED_BODY()

public:
	FPickupItem() :
		PickupQuantity(0),
		ResourceType(EResourceType::Wood),
		PickupStorage(nullptr)
	{}

	FPickupItem(enum EResourceType InResourceType, int32 InPickupQuantity, USGInventoryComponent* InPickupStorage) :
		PickupQuantity(InPickupQuantity),
		ResourceType(InResourceType),
		PickupStorage(InPickupStorage)
	{}

	int32 PickupQuantity;
	enum EResourceType ResourceType;
	USGInventoryComponent* PickupStorage;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVALCITYBUILDER_API USGTransporterComponent : public USGJobBaseComponent
{
	GENERATED_BODY()

private:
	bool bCanStartJob = true;
	TMap<FGuid, FPickupItem> OngoingPickups;

public:	
	USGTransporterComponent();

	UPROPERTY(BlueprintReadOnly)
	TArray<TEnumAsByte<enum EResourceType>> ResourceTypesForTransport;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<ETransportReason> TransportReason;

	virtual void BeginPlay() override;

	virtual bool ValidateCanTakeJob(const FGuid OwnerGuid) final override;

	virtual void LeaveJobSlot(const FGuid OwnerGuid) final override;

	void ValidateResourceRequirements();

	FORCEINLINE virtual bool CanStartJobTask() final override
	{
		return bCanStartJob;
	}

	FORCEINLINE FPickupItem* GetAssignedPickupItem(const FGuid OwnerId)
	{
		return &*OngoingPickups.Find(OwnerId);
	}

protected:
	USGInventoryComponent* FindNearestStorage(enum EResourceType ResourceType);
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
};
