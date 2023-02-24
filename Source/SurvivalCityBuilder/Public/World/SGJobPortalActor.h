// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Jobs/SGJobComponentInterface.h"
#include "SGJobPortalActor.generated.h"

struct FJobPost
{
	int32 Id;
	ISGJobInterface* Job;

	FJobPost() : 
		Id(0), 
		Job(nullptr) 
	{};

	FJobPost(const int32 InId, ISGJobInterface* InJob) : 
		Id(InId), 
		Job(InJob) 
	{};
};

UCLASS()
class SURVIVALCITYBUILDER_API ASGJobPortalActor : public AActor
{
	GENERATED_BODY()
	
private:
	// List of job posted
	TArray<FJobPost> JobPortal;

public:
	ASGJobPortalActor();

	void Add(const int32 JobId, ISGJobInterface* Job);
	
	ISGJobInterface* SearchJob(TSubclassOf<class USGJobBaseComponent> JobComponentClass);

	ISGJobInterface* SearchJobByProfession(const enum EProfession Profession);
};
