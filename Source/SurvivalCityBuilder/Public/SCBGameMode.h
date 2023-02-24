// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SCBGameState.h"
#include "SCBGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALCITYBUILDER_API ASCBGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	class ASCBGameState* PlayerGameState;

	virtual void BeginPlay() override;

private:

	void SpawnSurvivors();

};
