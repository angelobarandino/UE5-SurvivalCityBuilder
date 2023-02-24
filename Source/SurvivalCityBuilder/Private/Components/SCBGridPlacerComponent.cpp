// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SCBGridPlacerComponent.h"
#include "Components/BoxComponent.h"
#include "Base/SCBBuildingBase.h"
#include "Player/SCBPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

USCBGridPlacerComponent::USCBGridPlacerComponent()
{
	GridMaterial = LoadObject<UMaterialInterface>(NULL, TEXT("/Game/SurvivalCityBuilder/GameObjects/Grid/MI_Grid"));
	ValidMaterial = LoadObject<UMaterialInterface>(NULL, TEXT("/Game/SurvivalCityBuilder/GameObjects/Grid/MI_GhostBuilding_Valid"));
	InvalidMaterial = LoadObject<UMaterialInterface>(NULL, TEXT("/Game/SurvivalCityBuilder/GameObjects/Grid/MI_GhostBuilding_Invalid"));
	PlaneStaticMesh = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/BasicShapes/Plane.Plane"));
	
	PrimaryComponentTick.bCanEverTick = true;
}

void USCBGridPlacerComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get owner actor
	OwnerActor = GetOwner();
	check(OwnerActor); 

	// Get owner actor box componennt
	ActorCollision = Cast<UBoxComponent>(OwnerActor->GetComponentByClass(UBoxComponent::StaticClass()));
	check(ActorCollision);

	// Get PlayerController
	PC = Cast<ASCBPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	check(PC);

	// Attach a static mesh component to actor for showing grid lines
	GridMesh = NewObject<UStaticMeshComponent>(GetOwner());
	GridMesh->SetStaticMesh(PlaneStaticMesh);
	GridMesh->SetMaterial(0, GridMaterial);
	GridMesh->SetWorldScale3D(FVector(GridSize.X * 8, GridSize.X * 8, 1.0f));
	GridMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GridMesh->AddRelativeLocation(FVector(0.0f, 0.0f, 10));
	GridMesh->SetCastShadow(false);
	GridMesh->AttachToComponent(OwnerActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	GridMesh->RegisterComponent();

	PlacerMesh = NewObject<UStaticMeshComponent>(GetOwner());
	PlacerMesh->SetStaticMesh(PlaneStaticMesh);
	PlacerMesh->SetMaterial(0, ValidMaterial);
	PlacerMesh->SetWorldScale3D(FVector(GridSize, 1.0f));
	PlacerMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PlacerMesh->AddRelativeLocation(FVector(0.0f, 0.0f, 5.0f));
	PlacerMesh->SetCastShadow(false);
	PlacerMesh->AttachToComponent(OwnerActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	PlacerMesh->RegisterComponent();

}

void USCBGridPlacerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// get mouse location in the world and transform to grid point
	FVector NewLocation;
	ConvertMouseToGridLocation(NewLocation);

	// Set actor new location
	FVector CurrentLocation = OwnerActor->GetActorLocation();
	OwnerActor->SetActorLocation(FMath::Lerp(CurrentLocation, NewLocation, LerpSpeed));

	// Check placement is valid
	TArray<AActor*> OverlappingActors;
	ActorCollision->GetOverlappingActors(OverlappingActors);
	bIsValidPlacementLocation = OverlappingActors.Num() == 0;

	// Assign material
	PlacerMesh->SetMaterial(0, bIsValidPlacementLocation ? ValidMaterial : InvalidMaterial);
}

void USCBGridPlacerComponent::SetGridSize(FVector2D Value)
{
	GridSize = Value;
}

void USCBGridPlacerComponent::ConvertMouseToGridLocation(FVector& Location)
{
	FVector WorldLocation, WorldDirection;
	PC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	FHitResult OutHit;
	FCollisionQueryParams CollisionParams;

	FVector Start = WorldLocation;
	FVector End = WorldLocation + WorldDirection * 10000.0f;

	if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_GameTraceChannel1, CollisionParams))
	{
		Location = OutHit.Location.GridSnap(100.0f);
	}
}