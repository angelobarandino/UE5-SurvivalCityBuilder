// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SCBWorkAreaComponent.generated.h"

class ASCBPlayerController;

/**
 * 
 */
UCLASS(ClassGroup=(BuildingComponents), meta=(BlueprintSpawnableComponent))
class SURVIVALCITYBUILDER_API USCBWorkAreaComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public: 

	USCBWorkAreaComponent();
	
	UPROPERTY(EditDefaultsOnly, Category = "Work Area")
	float MinRadius = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = "Work Area")
	float MaxRadius = 50.f;

protected:

	void BeginPlay() override;
};
