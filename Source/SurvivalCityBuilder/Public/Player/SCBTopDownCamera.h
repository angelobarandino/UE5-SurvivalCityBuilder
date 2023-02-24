// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputMappingContext.h"
#include "SCBTopDownCamera.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SURVIVALCITYBUILDER_API ASCBTopDownCamera : public APawn
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
	// Sets default values for this pawn's properties
	ASCBTopDownCamera();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UCameraComponent* Camera;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	int32 Priority;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TSoftObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* CameraMoveInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* CameraRotateStartInputAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* CameraRotateInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* CameraZoomInputAction;


	UPROPERTY(EditDefaultsOnly, Category = "Camera Movement")
	float CameraSmoothMovement = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Movement")
	float CameraMoveSpeed = 100.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera Movement")
	float CameraOrbitSpeed = 10.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera Movement")
	float ZoomingStepSpeed = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Movement")
	float ZoomingStepSize = 300.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera Movement")
	float ZoomMinDistance = 300.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera Movement")
	float ZoomMaxDistance = 10000.0f;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetSpringArmLength();

	UFUNCTION(BlueprintCallable)
	void SetSpringArmLength(float NewTargetArmLength);

private:

	void HandleMovement(const FInputActionValue& Value);
	void HandleRotateStart(const FInputActionValue& Value);
	void HandleRotate(const FInputActionValue& Value);
	void HandleZoom(const FInputActionValue& Value);
};
