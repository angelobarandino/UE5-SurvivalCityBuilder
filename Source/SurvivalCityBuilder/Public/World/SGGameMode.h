// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCITYBUILDER_API ASGGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASGGameMode();

	UPROPERTY(EditDefaultsOnly, Category = "Dev Test")
	int32 SurvivorsCount;

	UPROPERTY(EditDefaultsOnly, Category = "Dev Test")
	TSubclassOf<class ASGAICharacter> CharacterClass;

	
	UPROPERTY(EditDefaultsOnly,Category = "Character|Brain")
	TMap<TEnumAsByte<enum EProfession>, class UBehaviorTree*> CharacterBrains;

	virtual void BeginPlay() override;

	class UBehaviorTree* GetBrain(const enum EProfession Profession);

private:
	void SpawnSurvivors(const int32 ToSpawnCount);
};
