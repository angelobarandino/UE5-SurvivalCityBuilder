// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/BTDecorator_CheckProfession.h"
#include "AI/SGAIController.h"

bool UBTDecorator_CheckProfession::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (ASGAIController* Controller = Cast<ASGAIController>(OwnerComp.GetOwner()))
	{
		return Controller->Profession == Profession;
	}

	return false;
}
