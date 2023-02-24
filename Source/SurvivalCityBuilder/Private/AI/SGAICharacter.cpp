// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SGAICharacter.h"
#include "AI/SGAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ASGAICharacter::ASGAICharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	AIControllerClass = ASGAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

USGJobBaseComponent* ASGAICharacter::GetJobComponent()
{
	if (CurrentJobComponent == nullptr)
	{
		if (ASGAIController* CharacterController = Cast<ASGAIController>(GetController()))
		{
			CurrentJobComponent = CharacterController->GetJobComponent();
		}
	}

	return CurrentJobComponent;
}

void ASGAICharacter::BeginPlay()
{
	Super::BeginPlay();
}
