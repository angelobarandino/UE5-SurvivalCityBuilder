// Fill out your copyright notice in the Description page of Project Settings.


#include "SCBGameState.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "AI/SGAICharacter.h"
#include "AI/SGAIController.h"
#include "Buildings/SCBConstructionComponent.h"
#include "Buildings/SGBuildingActor.h"
#include "Jobs/SGJobBaseComponent.h"

ASCBGameState::ASCBGameState()
{

}

void ASCBGameState::AddSurvivor(ASGAICharacter* Character)
{
	Characters.Add(Character);
}
