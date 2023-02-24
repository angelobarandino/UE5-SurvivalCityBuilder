// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Jobs/SGJobs.h"
#include "GameplayHelpers.generated.h"

USTRUCT(BlueprintType)
struct FJobSearchResult
{
	GENERATED_BODY()

public:
	FJobSearchResult() :
		Key(FGuid::FGuid()),
		HasResult(false),
		Location(FVector::ZeroVector),
		Owner(nullptr),
		Job(nullptr)
	{}

	FGuid Key;

	UPROPERTY(BlueprintReadOnly)
	bool HasResult;
	
	UPROPERTY(BlueprintReadOnly)
	FVector Location;

	UPROPERTY(BlueprintReadOnly)
	class ASGBuildingActor* Owner;

	UPROPERTY(BlueprintReadOnly)
	USGJobBaseComponent* Job;
};

/**
 * 
 */
UCLASS(BlueprintType)
class SURVIVALCITYBUILDER_API UGameplayHelpers : public UBlueprintFunctionLibrary
{

	GENERATED_BODY()

public:

	static void CreateJobPost(const UWorld* World, class ISGJobInterface* JobComponent);
	static void RemoveJobPost(const UWorld* World, class ISGJobInterface* JobComponent);

	static FJobSearchResult SearchJobByProfession(const UWorld* World, const enum EProfession Profession);

	static FJobSearchResult SearchJobByClass(const UWorld* World, TSubclassOf<USGJobBaseComponent> JobComponentClass);

	UFUNCTION(BlueprintCallable, Category = "Gameplay Helpers")
	static FJobSearchResult SearchJobByProfession(const AActor* Actor, const enum EProfession Profession);

	UFUNCTION(BlueprintCallable, Category = "Gameplay Helpers")
	static FJobSearchResult SearchJobByClass(const AActor* Actor, TSubclassOf<USGJobBaseComponent> JobComponentClass);

	UFUNCTION(BlueprintPure, Category = "Gameplay Helpers")
	static class ASGBuildingActor* FindNearestBuildingWithComponentOfType(const AActor* ActorOrigin, TSubclassOf<UActorComponent> ComponentClass);

	UFUNCTION(BlueprintPure, Category = "Gameplay Helpers")
	static FName GetResourceTypeNameFromValue(const int32 EnumValue);

	UFUNCTION(BlueprintPure, Category = "Gameplay Helpers")
	static enum EResourceType GetResourceTypeValueFromName(const FName EnumName);

	UFUNCTION(BlueprintPure, Category = "Gameplay Helpers")
	static class ASGAIController* GetCharacterByOwnerId(const UWorld* World, const FGuid OwnerGuid);
};
