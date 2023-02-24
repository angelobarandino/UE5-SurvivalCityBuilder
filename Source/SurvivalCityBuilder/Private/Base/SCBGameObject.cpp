// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/SCBGameObject.h"
#include "Player/SCBPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASCBGameObject::ASCBGameObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bNotifyActorOnMouseEvents = true;
}


// Called when the game starts or when spawned
void ASCBGameObject::BeginPlay()
{
	Super::BeginPlay();

	// Get a reference to player controller
	PlayerController = Cast<ASCBPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	check(PlayerController);
}


USceneComponent* ASCBGameObject::GetMainTransformComponent()
{
	return GetRootComponent();
}


void ASCBGameObject::SetFocused(bool bIsFocused)
{
	bIsObjectFocused = bIsFocused;

	SetRenderCustomDepth(bIsFocused);
}


void ASCBGameObject::SetRenderCustomDepth(bool Value)
{
	USceneComponent* MainTransform = GetMainTransformComponent();

	if (MainTransform)
	{
		TArray<USceneComponent*> AttachedComponents = MainTransform->GetAttachChildren();

		for (USceneComponent* ChildComp : AttachedComponents)
		{
			if (UStaticMeshComponent* StaticMeshComp = Cast<UStaticMeshComponent>(ChildComp))
			{
				StaticMeshComp->SetRenderCustomDepth(Value);
			}
		}
	}
}


void ASCBGameObject::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	//if (!bNotifyActorOnMouseEvents) return;

	//PlayerController->OnInteract.Broadcast(this);
}


void ASCBGameObject::NotifyActorBeginCursorOver()
{
	Super::NotifyActorBeginCursorOver();

	if (!bNotifyActorOnMouseEvents || bIsObjectFocused) return;

	SetRenderCustomDepth(true);
}


void ASCBGameObject::NotifyActorEndCursorOver()
{
	Super::NotifyActorEndCursorOver();

	if (!bNotifyActorOnMouseEvents || bIsObjectFocused) return;

	SetRenderCustomDepth(false);
}
