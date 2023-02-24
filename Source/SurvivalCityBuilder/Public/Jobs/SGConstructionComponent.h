// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGGameplayTypes.h"
#include "SGJobBaseComponent.h"
#include "Components/ActorComponent.h"
#include "SGConstructionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALCITYBUILDER_API USGConstructionComponent : public USGJobBaseComponent
{
	GENERATED_BODY()

private:
	float CurrentProgress;

public:	
	USGConstructionComponent();

	virtual bool ValidateCanTakeJob(FGuid OwnerId) final override;

protected:
	virtual void BeginPlay() override;

};
