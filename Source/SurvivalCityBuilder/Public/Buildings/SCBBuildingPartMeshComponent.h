// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "SCBBuildingPartMeshComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVALCITYBUILDER_API USCBBuildingPartMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	USCBBuildingPartMeshComponent();

	UPROPERTY(EditDefaultsOnly, Category = "Building Construction")
	float ShowProgress;

public:
	void OnConstructionProgress(const float Progress);
};
