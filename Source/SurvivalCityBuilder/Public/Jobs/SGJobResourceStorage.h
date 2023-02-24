// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/SGResourceType.h"
#include "SGJobResourceStorage.generated.h"

USTRUCT(BlueprintType)
struct FSGResourceNeed
{
	GENERATED_BODY()

public:
	FSGResourceNeed() :
		ResourceAsset(nullptr),
		RequiredQuantity(0),
		CurrentQuantity(0)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Item")
	USGResourceType* ResourceAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource Item")
	int32 RequiredQuantity;

	int32 CurrentQuantity;
};
