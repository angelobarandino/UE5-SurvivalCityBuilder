// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SGGlobalInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALCITYBUILDER_API USGGlobalInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USGGlobalInventoryComponent();

	UPROPERTY(EditAnywhere, Category = "Inventory System")
	TArray<struct FSGResourceItem> GlobalResourceInventory;
};
