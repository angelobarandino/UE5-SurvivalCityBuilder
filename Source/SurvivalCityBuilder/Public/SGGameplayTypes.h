// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EProfession
{
	NoProfession	=	0 UMETA(DisplayName = "No Profession"),
	Laborer			=	1 UMETA(DisplayName = "Laborer"),
	Transporter		=	2 UMETA(DisplayName = "Transporter"),
	Builder			=	3 UMETA(DisplayName = "Builder"),
};

UENUM(BlueprintType)
enum EBuildingType
{
	None		= 0 UMETA(DisplayName = "None"),
	LumberYard	= 1 UMETA(DisplayName = "Lumber Yard"),
	StockPile	= 2 UMETA(DisplayName = "Stockpile")
};

UENUM(BlueprintType)
enum EResourceType
{
	Wood		= 0 UMETA(DisplayName = "Wood"),
	Gravel		= 1 UMETA(DisplayName = "Gravel"),
};

UENUM(BlueprintType)
enum EResourceStorageRule
{
	Both		= 0 UMETA(DisplayName = "Both"),
	InOnly		= 1 UMETA(DisplayName = "InOnly"),
	OutOnly		= 2 UMETA(DisplayName = "OutOnly"),
};