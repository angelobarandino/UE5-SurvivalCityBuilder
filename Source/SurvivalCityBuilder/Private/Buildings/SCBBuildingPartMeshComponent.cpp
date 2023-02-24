// Fill out your copyright notice in the Description page of Project Settings.

#include "Buildings/SCBBuildingPartMeshComponent.h"

USCBBuildingPartMeshComponent::USCBBuildingPartMeshComponent()
{
	SetMobility(EComponentMobility::Stationary);
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetCollisionResponseToAllChannels(ECR_Ignore);
}

void USCBBuildingPartMeshComponent::OnConstructionProgress(const float Progress)
{
	if (Progress >= ShowProgress)
	{
		SetVisibility(true);
	}
}
