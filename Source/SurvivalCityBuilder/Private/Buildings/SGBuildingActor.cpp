// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/SGBuildingActor.h"
#include "Inventory/SGInventoryComponent.h"
#include "Jobs/SGJobResourceStorage.h"
#include "Jobs/SGJobs.h"

ASGBuildingActor::ASGBuildingActor()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent->SetMobility(EComponentMobility::Stationary);

	SetRootComponent(RootComponent);
	MainTransform = CreateDefaultSubobject<USceneComponent>(TEXT("MainTransform"));
	MainTransform->SetMobility(EComponentMobility::Stationary);
	MainTransform->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetMobility(EComponentMobility::Stationary);
	BoxComponent->SetupAttachment(MainTransform);
}

void ASGBuildingActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASGBuildingActor::Interact(APawn* Interactor)
{

}

void ASGBuildingActor::SetMobility(EComponentMobility::Type Mobility)
{
	RootComponent->SetMobility(Mobility);
	MainTransform->SetMobility(Mobility);
	BoxComponent->SetMobility(Mobility);

	for (USceneComponent* ChildComp : MainTransform->GetAttachChildren())
	{
		ChildComp->SetMobility(Mobility);
	}
}

void ASGBuildingActor::SetUnderConstruction(bool bUnderConstruction)
{
	if (bUnderConstruction)
	{
		// Add building for construction job component
		USGConstructionComponent* ConstructionComp = NewObject<USGConstructionComponent>(this);
		ConstructionComp->SetMaxJobSlots(BuildingData->MaxBuilders);

		// Add buiding construction transport materials job component
		USGTransporterComponent* TransporterComp = NewObject<USGTransporterComponent>(this);
		TransporterComp->TransportReason = ETransportReason::FillMinQuantity;

		// Add building construction need resources
		USGInventoryComponent* InventoryComponent = NewObject<USGInventoryComponent>(this);
		InventoryComponent->StorageRule = EResourceStorageRule::InOnly;
		for (const FSGResourceNeed ResourceNeed : BuildingData->ConstructionNeeds)
		{
			const FSGResourceItem ResourceItem = FSGResourceItem::CreateMinMax(
				ResourceNeed.ResourceAsset, 
				ResourceNeed.RequiredQuantity,
				ResourceNeed.RequiredQuantity
			);

			InventoryComponent->AddResource(ResourceItem);
		}

		InventoryComponent->RegisterComponent();
		ConstructionComp->RegisterComponent();
		TransporterComp->RegisterComponent();
	}
}

bool ASGBuildingActor::IsUnderConstruction()
{
	// Check if actors contains construction component
	for (const UActorComponent* Component : GetComponents())
	{
		const USGConstructionComponent* CameraComponent = Cast<const USGConstructionComponent>(Component);
		if (CameraComponent)
		{
			return true;
		}
	}

	return false;
}
