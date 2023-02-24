// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include "SGGameplayTypes.h"
#include "SGBuildingData.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCITYBUILDER_API USGBuildingData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Data")
	UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Data")
	FString Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Data")
	TEnumAsByte<EBuildingType> BuildingType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Data")
	int32 MaxProductionWorkforce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Construction")
	int32 MaxBuilders;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Construction")
	float ConstructionCost;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Construction")
	TArray<struct FSGResourceNeed> ConstructionNeeds;
};
