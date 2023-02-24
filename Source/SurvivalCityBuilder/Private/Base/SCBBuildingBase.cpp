// Fill out your copyright notice in the Description page of Project Settings.

#include "Base/SCBBuildingBase.h"
#include "Buildings/SCBBuildingPartMeshComponent.h"
#include "Buildings/SCBConstructionComponent.h"
#include "Buildings/SCBWorkAreaComponent.h"
#include "Jobs/SGTransporterComponent.h"
#include "Components/BoxComponent.h"

ASCBBuildingBase::ASCBBuildingBase()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultScene"));
	RootComponent->SetMobility(EComponentMobility::Stationary);
	SetRootComponent(RootComponent);

	MainTransform = CreateDefaultSubobject<USceneComponent>(TEXT("MainTransform"));
	MainTransform->SetMobility(EComponentMobility::Stationary);
	MainTransform->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(MainTransform);

	bIsUnderConstruction = false;
}


void ASCBBuildingBase::BeginPlay()
{
	Super::BeginPlay();
}


USceneComponent* ASCBBuildingBase::GetMainTransformComponent()
{
	return MainTransform;
}


void ASCBBuildingBase::Interact(APawn* Interactor)
{

}

void ASCBBuildingBase::SetFocused(bool bIsInteracted)
{
	Super::SetFocused(bIsInteracted);
	
	// Check if building has work area component attached and toggle it's visibility
	if (USCBWorkAreaComponent* WorkAreaComponent = Cast<USCBWorkAreaComponent>(GetComponentByClass(USCBWorkAreaComponent::StaticClass())))
	{
		WorkAreaComponent->SetVisibility(bIsInteracted);
	}
}


void ASCBBuildingBase::SetMobility(EComponentMobility::Type Mobility)
{
	for (USceneComponent* ChildComp : MainTransform->GetAttachChildren())
	{
		if (USCBBuildingPartMeshComponent* BuildingPartMesh = Cast<USCBBuildingPartMeshComponent>(ChildComp))
		{
			BuildingPartMesh->SetMobility(Mobility);
			RootComponent->SetMobility(Mobility);
			MainTransform->SetMobility(Mobility);
		}
	}
}

void ASCBBuildingBase::SetUnderConstruction(bool bNewValue)
{
	bIsUnderConstruction = bNewValue;

	if (bIsUnderConstruction)
	{
		// Add transporter requirement
		USGTransporterComponent* TransporterComp = NewObject<USGTransporterComponent>(this);
		/*TransporterComp->SetNeededResources(BuildingData->ConstructionNeeds);
		TransporterComp->SetMaxJobsSlot(2);*/
		TransporterComp->RegisterComponent();

		// Add construction component to new building
		USCBConstructionComponent* ConstructionComp = NewObject<USCBConstructionComponent>(this);
		ConstructionComp->Cost = BuildingData->ConstructionCost;
		ConstructionComp->MaxBuilders = BuildingData->MaxBuilders;
		ConstructionComp->SetConstructionRequirement(BuildingData->ConstructionNeeds);
		ConstructionComp->RegisterComponent();
		ConstructionComp->OnConstructionComplete.AddUObject(this, &ASCBBuildingBase::OnConstructionComplete);
		
		SetBuildingPartsUnderConstruction(ConstructionComp);
		return;
	}

	// Destroy components not needed if building is
	if (USGTransporterComponent* TransporterComp = Cast<USGTransporterComponent>(GetComponentByClass(USGTransporterComponent::StaticClass())))
	{
		TransporterComp->DestroyComponent();
	}

	if (USCBConstructionComponent* ConstructionComp = Cast<USCBConstructionComponent>(GetComponentByClass(USCBConstructionComponent::StaticClass())))
	{
		ConstructionComp->OnConstructionComplete.RemoveAll(this);
		ConstructionComp->OnConstructionProgress.RemoveAll(this);
		ConstructionComp->DestroyComponent();
	}
}

void ASCBBuildingBase::OnConstructionComplete()
{
	SetUnderConstruction(false);
}

void ASCBBuildingBase::SetBuildingPartsUnderConstruction(USCBConstructionComponent* ConstructionComponent)
{
	for (USceneComponent* ChildComp : MainTransform->GetAttachChildren())
	{
		if (USCBBuildingPartMeshComponent* BuildingPartMesh = Cast<USCBBuildingPartMeshComponent>(ChildComp))
		{
			// Set building visibility to false
			BuildingPartMesh->SetVisibility(false);

			// Add listener for the construction progress in building part component
			ConstructionComponent->OnConstructionProgress.AddUObject(BuildingPartMesh, &USCBBuildingPartMeshComponent::OnConstructionProgress);
		}
	}
}