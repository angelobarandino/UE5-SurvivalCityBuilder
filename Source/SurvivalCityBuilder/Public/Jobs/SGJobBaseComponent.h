// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SGJobComponentInterface.h"
#include "SGJobBaseComponent.generated.h"

class ASGAICharacter;
class ASGBuildingActor;
struct FSGResourceNeed;

UCLASS(Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SURVIVALCITYBUILDER_API USGJobBaseComponent : public UActorComponent, public ISGJobInterface
{
	GENERATED_BODY()

private:
	class USGInventoryComponent* CurrentInventoryComp;

public:	
	USGJobBaseComponent();

	UPROPERTY(BlueprintReadOnly)
	FGuid JobKey;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EProfession> JobProfession;

	UPROPERTY(BlueprintReadOnly)
	int32 MaxJobSlotsCanTake;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FGuid> JobSlotOwnerKeys;

public:
	virtual void BeginPlay() override;
	virtual void OnComponentDestroyed(bool DestroyingHierarchy) override;

	UFUNCTION(BlueprintPure, Category = "Job Component")
	virtual FString GetJobName();

	virtual void SetMaxJobSlots(const int32 MaxJobSlots);

	class USGInventoryComponent* GetInventoryComponent();

#pragma region Inherited via ISGJobInterface
	UFUNCTION(BlueprintPure, Category = "Job Component")
	virtual FGuid GetJobKey() override;

	UFUNCTION(BlueprintPure, Category = "Job Component")
	virtual TEnumAsByte<EProfession> GetProfession() override;

	UFUNCTION(BlueprintPure, Category = "Job Component")
	virtual FVector GetJobLocation() override;

	UFUNCTION(BlueprintPure, Category = "Job Component")
	virtual ASGBuildingActor* GetOwnerBuilding() override;

	UFUNCTION(BlueprintPure, Category = "Job Component")
	virtual bool HasJobSlot() override;

	UFUNCTION(BlueprintPure, Category = "Job Component")
	virtual bool ValidateCanTakeJob(const FGuid OwnerGuid) override;

	UFUNCTION(BlueprintCallable, Category = "Job Component")
	virtual bool TakeJobSlot(const FGuid OwnerGuid) override;

	UFUNCTION(BlueprintCallable, Category = "Job Component")
	virtual void LeaveJobSlot(const FGuid OWnerGuid) override;
	
	UFUNCTION(BlueprintCallable, Category = "Job Component")
	virtual bool CanStartJobTask() override;

	UFUNCTION(BlueprintCallable, Category = "Job Component")
	virtual bool DoJobTask(const float IncrementAmount) override;
#pragma endregion
};
