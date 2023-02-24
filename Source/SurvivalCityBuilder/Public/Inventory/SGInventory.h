#pragma once

#include "CoreMinimal.h"
#include "SGResourceType.h"
#include "SGGameplayTypes.h"
#include "SGInventory.generated.h"

USTRUCT(BlueprintType)
struct FSGResourceItem
{
	GENERATED_BODY()
public:

	FSGResourceItem():
		ResourceAsset(nullptr),
		MaxQuantity(500),
		MinQuantity(0),
		Quantity(0)
		//Rule(0)
	{}

	FSGResourceItem(USGResourceType* InResourceAsset, const int32 InMaxQuantity, const int32 InMinQuantity, const int32 InQuantity) :
		ResourceAsset(InResourceAsset),
		MaxQuantity(InMaxQuantity),
		MinQuantity(InMinQuantity),
		Quantity(InQuantity)
		//Rule(InStorageRule)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Item")
	USGResourceType* ResourceAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Item")
	int32 MaxQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Item")
	int32 MinQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Item")
	int32 Quantity;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Item")
	//TEnumAsByte<EResourceStorageRule> Rule;

	inline static FSGResourceItem Create(USGResourceType* InResourceAsset)
	{
		return FSGResourceItem(InResourceAsset, 0, 0, 0);
	}

	inline static FSGResourceItem CreateMin(USGResourceType* InResourceAsset, int32 InMinQuantity)
	{
		return FSGResourceItem(InResourceAsset, 0, InMinQuantity, 0);
	}

	inline static FSGResourceItem CreateMinMax(USGResourceType* InResourceAsset, int32 InMinQuantity, int32 InMaxQuantity)
	{
		return FSGResourceItem(InResourceAsset, InMaxQuantity, InMinQuantity, 0);
	}
};
