// Fill out your copyright notice in the Description page of Project Settings.

#include "World/SGGameState.h"
#include "Jobs/SGJobPortalComponent.h"
#include "Inventory/SGGlobalInventoryComponent.h"
#include "AI/SGAIController.h"

ASGGameState::ASGGameState()
{
	// Create USGGlobalInventoryComponent
	GlobalInventoryComp = CreateDefaultSubobject<USGGlobalInventoryComponent>(TEXT("GlobalInventoryComp"));

	// Create USGJobPortalComponent
	JobPortalComp = CreateDefaultSubobject<USGJobPortalComponent>(TEXT("JobPortalComp"));
}

USGGlobalInventoryComponent* ASGGameState::GetGlobalInventoryComponent()
{
	return GlobalInventoryComp;
}

USGJobPortalComponent* ASGGameState::GetJobPortalComponent()
{
	return JobPortalComp;
}

void ASGGameState::AddController(ASGAIController* NewController)
{
	if (!GameAIControllers.Contains(NewController->ControllerGuid))
	{
		GameAIControllers.Add(NewController->ControllerGuid, NewController);
	}
}
