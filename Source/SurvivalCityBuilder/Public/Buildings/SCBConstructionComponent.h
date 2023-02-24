// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGBuildingData.h"
#include "Components/ActorComponent.h"
#include "SCBConstructionComponent.generated.h"

class ASGAICharacter;

DECLARE_EVENT(USCBConstructionComponent, FConstructionComplete);
DECLARE_EVENT_OneParam(USCBConstructionComponent, FConstructionProgress, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALCITYBUILDER_API USCBConstructionComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	bool bIsConstructionComplete;
	float ConstructionProgress;

public:	
	// Sets default values for this component's properties
	USCBConstructionComponent();

	UPROPERTY(BlueprintReadOnly, Category = "Building Construction")
	float ConstructionPercentage;

	UPROPERTY(BlueprintReadWrite, Category = "Building Construction")
	int32 ConstructionPriority;

	UPROPERTY(BlueprintReadOnly, Category = "Building Construction")
	float Cost;

	UPROPERTY(BlueprintReadOnly, Category = "Building Construction")
	float MaxBuilders;
	
	UPROPERTY(BlueprintReadOnly, Category = "Building Construction")
	TArray<ASGAICharacter*> AssignedBuilders;

	UPROPERTY(BlueprintReadOnly, Category = "Building Construction")
	TArray<FSGResourceNeed> Requirements;

	FConstructionComplete OnConstructionComplete;
	FConstructionProgress OnConstructionProgress;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable, Category = "Building Construction")
	bool AddConstructionProgress(float Progress);

	UFUNCTION(BlueprintCallable, Category = "Building Construction")
	bool AssignBuilder(ASGAICharacter* Builder);

	bool IsBuildersFull();
	
	void SetConstructionRequirement(TArray<FSGResourceNeed> ConstructionNeeds);
};
