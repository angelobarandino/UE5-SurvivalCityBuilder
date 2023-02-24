// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Interfaces/SGInteractInterface.h"
#include "SGBuildingData.h"
#include "SGBuildingActor.generated.h"

UCLASS()
class SURVIVALCITYBUILDER_API ASGBuildingActor : public AActor, public ISGInteractInterface
{
	GENERATED_BODY()
	
public:	
	ASGBuildingActor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Building Data")
	USGBuildingData* BuildingData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Building Data")
	FVector2D GridSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	USceneComponent* MainTransform;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxComponent;

protected:
	virtual void BeginPlay() override;

public:	
	// Inherited via ISGInteractInterface
	virtual void Interact(APawn* Interactor) override;

	// Update all scene components mobility
	void SetMobility(EComponentMobility::Type Mobility);
	
	// Setup building for construction
	void SetUnderConstruction(bool bUnderConstruction);

	UFUNCTION(BlueprintPure)
	bool IsUnderConstruction();
};
