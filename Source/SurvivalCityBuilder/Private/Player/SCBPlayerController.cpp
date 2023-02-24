// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SCBPlayerController.h"
#include "Buildings/SGBuildingActor.h"
#include "Buildings/SCBConstructionComponent.h"
#include "Components/SCBGridPlacerComponent.h"
#include "Player/SCBTopDownCamera.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"

ASCBPlayerController::ASCBPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	bEnableMouseOverEvents = true;
}

void ASCBPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ASCBPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASCBPlayerController::SetInteractedObject(ASGBuildingActor* ClickedActor)
{
	OnInteract.Broadcast(ClickedActor);

	// Check if current and clicked actor are the same
	if (InteractedActor == ClickedActor)
		return;

	// Turn off custom depth to previous selected actor
	//if (InteractedActor != nullptr)
		//InteractedActor->SetFocused(false);

	// Turn on custom depth to newly selected actor
	//if (ClickedActor != nullptr)
		//ClickedActor->SetFocused(true);

	InteractedActor = ClickedActor;
}


void ASCBPlayerController::SetBuildModeActive(bool bBuildModeActive, TSubclassOf<ASGBuildingActor> BuildingClass)
{
	if (bIsBuildModeActivated == bBuildModeActive)
		return;

	GhostBuildingClass = BuildingClass;
	bIsBuildModeActivated = bBuildModeActive;
	OnBuildModeChanged(bBuildModeActive);
}

void ASCBPlayerController::CreateGhostBuilding(TSubclassOf<ASGBuildingActor> BuildingClass)
{
	// Create spawn parameters
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = UGameplayStatics::GetPlayerPawn(this, 0);
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FTransform Transform(FRotator::ZeroRotator, FVector(0, 0, -10000), FVector::OneVector);
	GhostBuildingRef = GetWorld()->SpawnActor<ASGBuildingActor>(BuildingClass, Transform, SpawnParameters);
	if (GhostBuildingRef == nullptr)
		return;

	// Set actor mobility to movable and disable mouse events
	GhostBuildingRef->SetMobility(EComponentMobility::Movable);
	//GhostBuildingRef->bNotifyActorOnMouseEvents = false;
	//GhostBuildingRef->SetFocused(true);

	// Attach a grid placer component
	USCBGridPlacerComponent* GridComponent = NewObject<USCBGridPlacerComponent>(GhostBuildingRef);
	GridComponent->SetGridSize(GhostBuildingRef->GridSize);
	GridComponent->RegisterComponent();
}

void ASCBPlayerController::ConfirmBuildingPlacement()
{
	if (bIsBuildModeActivated && GhostBuildingRef != nullptr)
	{
		if (USCBGridPlacerComponent* GridPlacerComp = Cast<USCBGridPlacerComponent>(GhostBuildingRef->GetComponentByClass(USCBGridPlacerComponent::StaticClass())))
		{
			// Check if location is valid
			if (!GridPlacerComp->bIsValidPlacementLocation)
				return;

			// Create spawn parameters
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Instigator = UGameplayStatics::GetPlayerPawn(this, 0);
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			// Spawn a new building
			ASGBuildingActor* NewBuilding = GetWorld()->SpawnActor<ASGBuildingActor>(
				GhostBuildingRef->GetClass(),
				GhostBuildingRef->GetTransform(),
				SpawnParameters
			);

			if (NewBuilding)
			{
				// Set building to under construction
				NewBuilding->SetUnderConstruction(true);
				NewBuilding->SetMobility(EComponentMobility::Stationary);

				// Deactivate build mode
				bIsBuildModeActivated = false;
				OnBuildModeChanged(false);
			}
		}
	}
}
