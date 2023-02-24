// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/SCBWorkAreaComponent.h"
#include "Player/SCBPlayerController.h"
#include "Base/SCBBuildingBase.h"
#include "Kismet/GameplayStatics.h"

USCBWorkAreaComponent::USCBWorkAreaComponent()
{
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SetStaticMesh(LoadObject<UStaticMesh>(NULL, TEXT("/Engine/BasicShapes/Plane.Plane")));
	SetMaterial(0, LoadObject<UMaterialInstance>(NULL, TEXT("/Game/SurvivalCityBuilder/GameObjects/WorkArea/MI_WorkArea")));
}

void USCBWorkAreaComponent::BeginPlay()
{
	SetVisibility(false);
	SetRelativeLocation(FVector(0, 0, 50.f));
	SetWorldScale3D(FVector(MinRadius, MinRadius, 1));

	ASCBBuildingBase* BuildingActor = Cast<ASCBBuildingBase>(GetOwner());
	check(BuildingActor);
}
