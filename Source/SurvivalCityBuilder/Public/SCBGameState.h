// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Jobs/SGJobComponentInterface.h"
#include "SCBGameState.generated.h"

class ASGAICharacter;
class ASCBBuildingBase;
class USGJobBaseComponent;

/**
 * 
 */
UCLASS()
class SURVIVALCITYBUILDER_API ASCBGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ASCBGameState();

	UPROPERTY(EditDefaultsOnly)
	TArray<TEnumAsByte<enum EProfession>> Survivors;

	UPROPERTY(BlueprintReadOnly)
	TArray<ASGAICharacter*> Characters;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "NPC")
	TSubclassOf<ASGAICharacter> AICharacterClass;

public:
	void AddSurvivor(ASGAICharacter* Survivor);
};
