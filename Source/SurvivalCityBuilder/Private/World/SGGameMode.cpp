// Fill out your copyright notice in the Description page of Project Settings.


#include "World/SGGameMode.h"
#include "World/SGGameState.h"
#include "AI/SGAICharacter.h"
#include "AI/SGAIController.h"
#include "BehaviorTree/BehaviorTree.h"

ASGGameMode::ASGGameMode()
{
	// Load and set our default game state class
	GameStateClass = ASGGameState::StaticClass();

	/*static ConstructorHelpers::FClassFinder<AGameStateBase> DefaultGameStateClass(TEXT("/Game/SurvivalCityBuilder/GameObjects/World/BP_GameState"));
	if (DefaultGameStateClass.Succeeded())
	{
		GameStateClass = DefaultGameStateClass.Class;
	}*/

	// Load and set our default pawn class
	static ConstructorHelpers::FClassFinder<APawn> DefaultTopDownPawnClass(TEXT("/Game/SurvivalCityBuilder/GameObjects/Player/BP_TopDownCamera"));
	if (DefaultTopDownPawnClass.Succeeded())
	{
		DefaultPawnClass = DefaultTopDownPawnClass.Class;
	}

	// Load and set our default player controller class
	static ConstructorHelpers::FClassFinder<APlayerController> DefaultPlayerControllerClass(TEXT("/Game/SurvivalCityBuilder/GameObjects/Player/BP_PlayerController"));
	if (DefaultPlayerControllerClass.Succeeded())
	{
		PlayerControllerClass = DefaultPlayerControllerClass.Class;
	}

	// Load and set our default player hud class
	static ConstructorHelpers::FClassFinder<AHUD> DefaultPlayerGameHUDClass(TEXT("/Game/SurvivalCityBuilder/UI/BP_GameHUD"));
	if (DefaultPlayerGameHUDClass.Succeeded())
	{
		HUDClass = DefaultPlayerGameHUDClass.Class;
	}
}

void ASGGameMode::BeginPlay()
{
	Super::BeginPlay();

	SpawnSurvivors(SurvivorsCount);
}

UBehaviorTree* ASGGameMode::GetBrain(const EProfession Profession)
{
	return *CharacterBrains.Find(Profession);
}

void ASGGameMode::SpawnSurvivors(const int32 ToSpawnCount)
{
	if (ASGGameState* NewGameState = GetGameState<ASGGameState>())
	{
		for (int32 i = 0; i < ToSpawnCount; i++)
		{
			FVector RandomLocation = FMath::RandPointInBox(FBox(
				FVector(-1000.f, -1000.f, 0.f),
				FVector(1000.f, 1000.f, 0.f)
			));

			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			// Spawn New AI Surivor Character
			ASGAICharacter* AICharacter = GetWorld()->SpawnActor<ASGAICharacter>(CharacterClass, RandomLocation, FRotator::ZeroRotator, SpawnParameters);

			// Spawn New AI Controller
			ASGAIController* AIController = GetWorld()->SpawnActor<ASGAIController>(SpawnParameters);
			AIController->ControllerGuid = FGuid::NewGuid();
			AIController->Possess(AICharacter);

			// Add New AI Controller to game state
			NewGameState->AddController(AIController);
		}
	}

}
