// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AI/SGAIController.h"
#include "Jobs/SGJobBaseComponent.h"
#include "SGGameplayTypes.h"
#include "SGAICharacter.generated.h"

UCLASS()
class SURVIVALCITYBUILDER_API ASGAICharacter : public ACharacter
{
	GENERATED_BODY()

private:
	USGJobBaseComponent* CurrentJobComponent;

public:
	ASGAICharacter();

	UPROPERTY(EditDefaultsOnly, Category = "Character Gameplay|Transporter")
	int32 MaxCarryCapacity = 20;

	UFUNCTION(BlueprintPure)
	FORCEINLINE FString GetCharacterName()
	{
		return *GetFName().ToString();
	}

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetCarryCapacity()
	{
		return 20;
	}

	UFUNCTION(BlueprintPure)
	USGJobBaseComponent* GetJobComponent();

protected:
	virtual void BeginPlay() override;

};
