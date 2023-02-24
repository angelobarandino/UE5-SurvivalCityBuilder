// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Base/SCBGameObject.h"
#include "Buildings/SGBuildingData.h"
#include "Interfaces/SGInteractInterface.h"
#include "SCBBuildingBase.generated.h"

class UBoxComponent;
class USCBWorkAreaComponent;
class USCBConstructionComponent;
class USCBBuildingPartMeshComponent;

/**
 * 
 */
UCLASS()
class SURVIVALCITYBUILDER_API ASCBBuildingBase : public ASCBGameObject, public ISGInteractInterface
{
	GENERATED_BODY()

public:
	ASCBBuildingBase();

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USceneComponent* MainTransform;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UBoxComponent* BoxComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Building Construction")
	bool bIsUnderConstruction;

	UPROPERTY(EditDefaultsOnly, Category = "Building Data")
	USGBuildingData* BuildingData;

protected:

	virtual void BeginPlay() override;

	virtual USceneComponent* GetMainTransformComponent() override;

public:

	// Inherited via ISGInteractInterface
	virtual void Interact(APawn* Interactor) override;

	virtual void SetFocused(bool bIsInteracted) override;

	void SetMobility(EComponentMobility::Type Mobility);

	void SetUnderConstruction(bool bNewValue);

private:

	void OnConstructionComplete();

	void SetBuildingPartsUnderConstruction(USCBConstructionComponent* ConstructionComponent);
};
