// Fill out your copyright notice in the Description page of Project Settings.


#include "Jobs/SGJobPortalComponent.h"
#include "Jobs/SGJobComponentInterface.h"
#include "Jobs/SGJobBaseComponent.h"
#include "SGGameplayTypes.h"

USGJobPortalComponent::USGJobPortalComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USGJobPortalComponent::BeginPlay()
{
	Super::BeginPlay();
}


void USGJobPortalComponent::CreateJobPost(ISGJobInterface* JobComponent)
{
	if (JobComponent != nullptr)
	{
		if (!AvailableJobs.Contains(JobComponent->GetJobKey()))
		{
			OnJobPostCreated.Broadcast(JobComponent);

			AvailableJobs.Add(JobComponent->GetJobKey(), JobComponent);
		}
	}
}

void USGJobPortalComponent::RemoveJobPost(ISGJobInterface* JobComponent)
{
	if (JobComponent != nullptr)
	{
		if (ISGJobInterface* JobComp = *AvailableJobs.Find(JobComponent->GetJobKey()))
		{
			//OnJobPostRemoved.Broadcast(JobComp);
			
			AvailableJobs.Remove(JobComp->GetJobKey());
		}
	}
}

ISGJobInterface* USGJobPortalComponent::SearchJobByProfession(const EProfession Profession)
{
	for (const auto& Job : AvailableJobs)
	{
		if (Job.Value != nullptr)
		{
			if (Job.Value->HasJobSlot() && Job.Value->CanStartJobTask())
			{
				if (Profession == EProfession::Laborer)
				{
					return Job.Value;
				}

				if (Profession == Job.Value->GetProfession())
				{
					return Job.Value;
				}
			}
		}
	}

	return nullptr;
}

ISGJobInterface* USGJobPortalComponent::SearchJobByClass(TSubclassOf<USGJobBaseComponent> JobComponentClass)
{
	for (const auto& Job : AvailableJobs)
	{
		if (Job.Value)
		{
			if (Job.Value->HasJobSlot() && Job.Value->CanStartJobTask())
			{
				if (USGJobBaseComponent* JobComp = Cast<USGJobBaseComponent>(Job.Value))
				{
					if (JobComp->GetClass()->IsChildOf(JobComponentClass))
					{
						return Job.Value;
					}
				}
			}
		}
	}

	return nullptr;
}