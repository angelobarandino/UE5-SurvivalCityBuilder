// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SCBPlayerController.generated.h"

class ASCBTopDownCamera;
class ASGBuildingActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractEventDispatcher, ASGBuildingActor*, BuildingActor);

/**
 * 
 */
UCLASS()
class SURVIVALCITYBUILDER_API ASCBPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	// Variables for controlling camera movement
	FVector CameraNewLocation;

	// Variables for controlling camera zoom in/out
	float CameraZoomTimer;
	float CameraNewZoomDistance;

	// Variables for controlling camera rotation
	bool bCameraRotate;
	FRotator CameraNewRotation;
	FVector2D CachedMousePosition;


public:
	
	ASCBPlayerController();

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay")
	ASGBuildingActor* InteractedActor;

	// Event Dispatchers
	UPROPERTY(BlueprintAssignable, Category = "Event Dispatcher")
	FInteractEventDispatcher OnInteract;

	// Building mode
	UPROPERTY(BlueprintReadOnly, Category = "Building Construction")
	ASGBuildingActor* GhostBuildingRef;

	// Building mode
	UPROPERTY(BlueprintReadOnly, Category = "Building Construction")
	TSubclassOf<ASGBuildingActor> GhostBuildingClass;

	UPROPERTY(BlueprintReadOnly, Category = "Building Construction")
	bool bIsBuildModeActivated;

protected:
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void SetInteractedObject(ASGBuildingActor* BuildingActor);

#pragma region Building Mode

	UFUNCTION(BlueprintCallable, Category = "Building Mode")
	void SetBuildModeActive(bool bBuildModeActive, TSubclassOf<ASGBuildingActor> BuildingClass);

	UFUNCTION(BlueprintCallable, Category = "Building Mode")
	void CreateGhostBuilding(TSubclassOf<ASGBuildingActor> BuildingClass);

	UFUNCTION(BlueprintCallable, Category = "Building Mode")
	void ConfirmBuildingPlacement();

	UFUNCTION(BlueprintImplementableEvent, Category = "Building Mode")
	void OnBuildModeChanged(bool bBuildModeActive);

#pragma endregion
};
