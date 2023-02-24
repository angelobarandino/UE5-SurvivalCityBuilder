// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SGGameplayTypes.h"
#include "Jobs/SGJobBaseComponent.h"
#include "SGAIController.generated.h"

class UBehaviorTree;
class ASGAICharacter;
class ISGJobInterface;

/**
 * 
 */
UCLASS()
class SURVIVALCITYBUILDER_API ASGAIController : public AAIController
{
	GENERATED_BODY()

private:
	class ASGGameMode* CurrentGameMode;
	
	ISGJobInterface* CurrentJobComponent;

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

public:

	UPROPERTY(BlueprintReadOnly)
	FGuid ControllerGuid;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EProfession> Profession;

	UFUNCTION()
	void RunBrain(const EProfession AIProfession);

	bool TakeJob(ISGJobInterface* JobComponent);
	bool HasJobComponent();
	bool LeaveJob();

	UFUNCTION(BlueprintPure)
	FORCEINLINE ASGAICharacter* GetCharacter()
	{
		return Cast<ASGAICharacter>(GetPawn());
	}
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE FGuid GetCurrentJobKey()
	{
		return CurrentJobComponent->GetJobKey();
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE USGJobBaseComponent* GetJobComponent()
	{
		return Cast<USGJobBaseComponent>(CurrentJobComponent);
	}

	template <typename T, typename USGJobBaseComponent = typename std::enable_if<std::is_base_of<USGJobBaseComponent, T>::value>::type>
	UFUNCTION(BlueprintCallable)
	FORCEINLINE T* GetJobComponent()
	{
		return Cast<T>(CurrentJobComponent);
	}
private:
	void OnJobPostCreated(ISGJobInterface* JobComponent);
	void OnJobPostRemoved(ISGJobInterface* JobComponent);
	void InitBlackboardVariables();
};
