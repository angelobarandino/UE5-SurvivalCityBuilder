// Fill out your copyright notice in the Description page of Project Settings.


#include "World/SGJobPortalActor.h"
#include "Buildings/SGBuildingActor.h"
#include "Jobs/SGJobComponentInterface.h"
#include "Jobs/SGJobBaseComponent.h"

ASGJobPortalActor::ASGJobPortalActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASGJobPortalActor::Add(const int32 JobId, ISGJobInterface* Job)
{
	if (Job)
	{
		bool bJobExist = JobPortal.ContainsByPredicate([JobId](FJobPost JP)
			{
				return JP.Id == JobId;
			});

		if (!bJobExist)
		{
			JobPortal.Add(FJobPost(JobId, Job));
		}
	}
}

ISGJobInterface* ASGJobPortalActor::SearchJob(TSubclassOf<USGJobBaseComponent> JobComponentClass)
{
	for (FJobPost JobPost : JobPortal)
	{
		if (Cast<USGJobBaseComponent>(JobPost.Job)->GetClass()->IsChildOf(JobComponentClass))
		{
			return JobPost.Job;
		}
	}

	return nullptr;
}

ISGJobInterface* ASGJobPortalActor::SearchJobByProfession(const EProfession Profession)
{
	for (FJobPost JobPost : JobPortal)
	{
		if (JobPost.Job)
		{
			if (Profession == EProfession::Laborer)
			{
				return JobPost.Job;
			}

			if (Profession == JobPost.Job->GetProfession())
			{
				return JobPost.Job;
			}
		}
	}

	return nullptr;
}

