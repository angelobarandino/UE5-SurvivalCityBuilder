// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SGGameState.generated.h"

class ASGAIController;
class USGGlobalInventoryComponent;
class USGJobPortalComponent;

/**
 * 
 */
UCLASS()
class SURVIVALCITYBUILDER_API ASGGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ASGGameState();

	UPROPERTY(BlueprintReadOnly, Category = "AI")
	TMap<FGuid, ASGAIController*> GameAIControllers;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USGGlobalInventoryComponent* GlobalInventoryComp;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
	USGJobPortalComponent* JobPortalComp;

public:
	USGJobPortalComponent* GetJobPortalComponent();
	USGGlobalInventoryComponent* GetGlobalInventoryComponent();

	void AddController(ASGAIController* NewController);

	UFUNCTION(BlueprintCallable)
	FORCEINLINE ASGAIController* GetCharacterByOwnerId(const FGuid OwnerId)
	{
		return *GameAIControllers.Find(OwnerId);
	}
};
