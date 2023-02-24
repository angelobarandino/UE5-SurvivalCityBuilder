// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SCBGameObject.generated.h"

class ASCBPlayerController;

UCLASS()
class SURVIVALCITYBUILDER_API ASCBGameObject : public AActor
{
	GENERATED_BODY()

private:
	// Use for controlling if building is selected or not
	bool bIsObjectFocused;

public:	

	// Sets default values for this actor's properties
	ASCBGameObject();

	ASCBPlayerController* PlayerController;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Object Info")
	FString ObjectName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Object Info")
	FVector2D GridSize;

	bool bNotifyActorOnMouseEvents;

protected:

	virtual void BeginPlay() override;

	virtual USceneComponent* GetMainTransformComponent();

public:

	UFUNCTION(BlueprintCallable)
	virtual void SetFocused(bool bIsFocused);

	void SetRenderCustomDepth(bool Value);
	
	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;

	virtual void NotifyActorBeginCursorOver() override;

	virtual void NotifyActorEndCursorOver() override;
};
