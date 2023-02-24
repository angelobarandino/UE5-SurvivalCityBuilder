// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/SCBConstructionComponent.h"

// Sets default values for this component's properties
USCBConstructionComponent::USCBConstructionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USCBConstructionComponent::BeginPlay()
{
	Super::BeginPlay();

	ConstructionProgress = 0;
	ConstructionPercentage = 0;
	bIsConstructionComplete = false;
}

bool USCBConstructionComponent::AddConstructionProgress(float Progress)
{
	if (bIsConstructionComplete || Cost == 0)
		return false;

	ConstructionProgress += Progress;
	ConstructionPercentage = ConstructionProgress / Cost;
	OnConstructionProgress.Broadcast(ConstructionPercentage * 100.0f);

	bIsConstructionComplete = ConstructionPercentage >= 1;
	if (bIsConstructionComplete)
	{
		OnConstructionComplete.Broadcast();
	}
	return bIsConstructionComplete;
}

bool USCBConstructionComponent::AssignBuilder(ASGAICharacter* Builder)
{
	if (AssignedBuilders.Num() == MaxBuilders)
		return false;

	if (AssignedBuilders.Find(Builder) != INDEX_NONE)
		return false;

	AssignedBuilders.Add(Builder);
	return true;
}

bool USCBConstructionComponent::IsBuildersFull()
{
	return AssignedBuilders.Num() == MaxBuilders;
}

void USCBConstructionComponent::SetConstructionRequirement(TArray<FSGResourceNeed> ConstructionNeeds)
{
	Requirements.Empty();
	for (FSGResourceNeed Item : ConstructionNeeds)
		Requirements.Add(Item);
}

