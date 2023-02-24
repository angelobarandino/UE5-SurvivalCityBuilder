// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SCBGridPlacerComponent.generated.h"

class UBoxComponent;
class ASCBPlayerController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALCITYBUILDER_API USCBGridPlacerComponent : public UActorComponent
{
	GENERATED_BODY()

	const float LerpSpeed = 0.45f;

private:
	// Reference to building grid size
	FVector2D GridSize;

	AActor* OwnerActor;
	UBoxComponent* ActorCollision;
	
	ASCBPlayerController* PC;

	UStaticMesh* PlaneStaticMesh;
	UStaticMeshComponent* GridMesh;
	UStaticMeshComponent* PlacerMesh;

	UMaterialInterface* GridMaterial;
	UMaterialInterface* ValidMaterial;
	UMaterialInterface* InvalidMaterial;

public:	
	// Sets default values for this component's properties
	USCBGridPlacerComponent();

	UPROPERTY(BlueprintReadOnly)
	bool bIsValidPlacementLocation;

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ConvertMouseToGridLocation(FVector& Location);

	void SetGridSize(FVector2D Value);
};
