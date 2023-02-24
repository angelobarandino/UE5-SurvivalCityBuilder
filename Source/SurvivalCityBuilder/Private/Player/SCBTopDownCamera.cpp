// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SCBTopDownCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Player/SCBPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
ASCBTopDownCamera::ASCBTopDownCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Scene Root Component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(RootComponent);

	// Create SpringArm Component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->SetRelativeRotation(FRotator(-50, 0, 0));
	SpringArm->bDoCollisionTest = false;
	SpringArm->TargetArmLength = 1500;

	// Create Camera Component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}


void ASCBTopDownCamera::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Move camera to new location
	if (!CameraNewLocation.IsZero())
	{
		FVector ActorLocation = GetActorLocation();
		FVector NewActorLocation = ActorLocation + CameraNewLocation;
		SetActorLocation(FMath::Lerp(
			ActorLocation,
			NewActorLocation,
			CameraSmoothMovement
		));
	}

	// Set camera new ratation
	if (bCameraRotate)
	{
		SetActorRotation(FMath::Lerp(
			GetActorRotation(), 
			CameraNewRotation, 
			CameraSmoothMovement)
		);
	}

	// Set camera zoom value
	if (CameraZoomTimer > 0)
	{
		CameraZoomTimer -= DeltaSeconds;
		SpringArm->TargetArmLength = FMath::Lerp(
			SpringArm->TargetArmLength,
			CameraNewZoomDistance,
			CameraSmoothMovement
		);
	}
}


void ASCBTopDownCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	ASCBPlayerController* PC = Cast<ASCBPlayerController>(GetController());
	check(PC);

	UEnhancedInputLocalPlayerSubsystem* InputSystem = PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(InputSystem);

	InputSystem->ClearAllMappings();
	InputSystem->AddMappingContext(InputMapping.LoadSynchronous(), Priority);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	Input->BindAction(CameraMoveInputAction, ETriggerEvent::Triggered, this, &ASCBTopDownCamera::HandleMovement);
	Input->BindAction(CameraRotateStartInputAction, ETriggerEvent::Triggered, this, &ASCBTopDownCamera::HandleRotateStart);
	Input->BindAction(CameraRotateInputAction, ETriggerEvent::Triggered, this, &ASCBTopDownCamera::HandleRotate);
	Input->BindAction(CameraZoomInputAction, ETriggerEvent::Triggered, this, &ASCBTopDownCamera::HandleZoom);
}


float ASCBTopDownCamera::GetSpringArmLength()
{
	for (USceneComponent* ChildComp : GetRootComponent()->GetAttachChildren())
	{
		if (USpringArmComponent* SpringComp = Cast<USpringArmComponent>(ChildComp))
		{
			return SpringComp->TargetArmLength;
		}
	}

	return ZoomMinDistance;
}


void ASCBTopDownCamera::SetSpringArmLength(float NewTargetArmLength)
{
	for (USceneComponent* ChildComp : GetRootComponent()->GetAttachChildren())
	{
		if (USpringArmComponent* SpringComp = Cast<USpringArmComponent>(ChildComp))
		{
			SpringComp->TargetArmLength = NewTargetArmLength;
		}
	}
}


void ASCBTopDownCamera::HandleMovement(const FInputActionValue& Value)
{
	FVector MoveVector = Value.Get<FVector>();

	// Get current actor rotation
	FRotator Rotation = GetActorRotation();

	// Set new forward vector based on current rotation
	FVector NewForwardVector = Rotation.Vector() * MoveVector.Y * CameraMoveSpeed;

	// Set new right vector based on current rotation
	FVector NewRightVector = Rotation.RotateVector(FVector::RightVector) * MoveVector.X * CameraMoveSpeed;

	// Set camera target location
	CameraNewLocation = NewRightVector + NewForwardVector;
}

void ASCBTopDownCamera::HandleRotateStart(const FInputActionValue& Value)
{
	bCameraRotate = Value.Get<bool>();
}

void ASCBTopDownCamera::HandleRotate(const FInputActionValue& Value)
{
	if (!bCameraRotate) return;
	
	float MouseDelta = Value.Get<float>();

	FRotator CameraRotation = GetActorRotation();
	CameraRotation.Yaw += MouseDelta * CameraOrbitSpeed;

	// Set camera target rotation
	CameraNewRotation = CameraRotation;
}

void ASCBTopDownCamera::HandleZoom(const FInputActionValue& Value)
{
	float ZoomDelta = Value.GetMagnitude();
	float ZoomDirection = FMath::Clamp(ZoomDelta, -3, 3);
	float CurrentDistance = SpringArm->TargetArmLength;
	float NewZoomDistance = CurrentDistance + ZoomingStepSize * ZoomDirection;

	// Set camera new zoom value
	CameraZoomTimer = ZoomingStepSpeed;
	CameraNewZoomDistance = FMath::Clamp(NewZoomDistance, ZoomMinDistance, ZoomMaxDistance);
}

