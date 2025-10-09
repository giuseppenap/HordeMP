// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_GameModeBase.h"

#include "EngineUtils.h"
#include "HMP_PlayerCharacter.h"
#include "HMP_PlayerState.h"
#include "HMP_SaveGame.h"
#include "SEnemyData.h"
#include "AI/HMP_AICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"


static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("hmp.SpawnBots"), true, TEXT("Enable spawning of bots via timer."), ECVF_Cheat);




AHMP_GameModeBase::AHMP_GameModeBase()
{
	SpawnTimerInterval = 2.0f;

	DesiredPowerupCount = 10;
	RequiredPowerupDistance = 2000;

	PlayerStateClass = AHMP_PlayerCharacter::StaticClass();

	CreditsToGrantOnKill = 500.0f;

	SlotName = "SaveGame01";
}

void AHMP_GameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	LoadSaveGame();
}

void AHMP_GameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &AHMP_GameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);

	if (ensure(PickupClasses.Num() > 0))
	{
		UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnPickupQuery, this, EEnvQueryRunMode::AllMatching, nullptr);
		if (ensure(QueryInstance))
		{
			QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AHMP_GameModeBase::OnPickupSpawnQueryCompleted);
		}
	}
}

void AHMP_GameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	AHMP_PlayerState* PS = NewPlayer->GetPlayerState<AHMP_PlayerState>();
	if (PS)
	{
		PS->LoadPlayerState(CurrentSaveGame);
	}

	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
}

void AHMP_GameModeBase::KillAll()
{
	for (AHMP_AICharacter* Bot:TActorRange<AHMP_AICharacter>(GetWorld()))
	{
		UHMP_AttributeComponent* AttributeComp = UHMP_AttributeComponent::GetAttributes(Bot);
		if (ensure(AttributeComp) && AttributeComp->IsAlive())
		{
			// @fixme: pass in player? for kill credits?
			for (AHMP_PlayerCharacter* Player:TActorRange<AHMP_PlayerCharacter>(GetWorld()))
			{
				if (Player)
				{
				AttributeComp->Kill(Player);
				}
			}
		}
	}
}

void AHMP_GameModeBase::SpawnBotTimerElapsed()
{
	if (!CVarSpawnBots.GetValueOnGameThread())
	{
		UE_LOG(LogTemp, Warning, TEXT("Bot spawning disabled via cvar `CVarSpawnBot`."));
		return;
	}

	int32 NrOfAliveBots = 0;
	for (AHMP_AICharacter* Bot:TActorRange<AHMP_AICharacter>(GetWorld()))
	{
		UHMP_AttributeComponent* AttributeComp = UHMP_AttributeComponent::GetAttributes(Bot);
		if (ensure(AttributeComp) && AttributeComp->IsAlive())
		{
			NrOfAliveBots++;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Found %i alive bots."), NrOfAliveBots);
	
	float MaxBotCount = 10.0f;
	
	if (DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	
	if (NrOfAliveBots >= MaxBotCount)
	{
		UE_LOG(LogTemp, Log, TEXT("At maximum bot capacity, skipping bot spawn."));
		return;
	}
	
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);

	if (ensure(QueryInstance))
	{
	QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AHMP_GameModeBase::OnSpawnBotQueryCompleted);
	}
}

void AHMP_GameModeBase::OnSpawnBotQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
	EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn bot Query EQS Failed!"))
		return;
	}

		
	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.IsValidIndex(0))
	{
		if (EnemyTable)
		{
			TArray<FEnemyInfoRow*> Rows;
			EnemyTable->GetAllRows("", Rows);

			//GetRandomEnemy
			int32 RandomIndex = FMath::RandRange(0, Rows.Num() - 1);
			FEnemyInfoRow* SelectedRow = Rows[RandomIndex];
			GetWorld()->SpawnActor<AActor>(SelectedRow->EnemyData->EnemyClass, Locations[0], FRotator::ZeroRotator);
		}
	}
}

void AHMP_GameModeBase::OnPickupSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
	EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn Pickup Query EQS Failed!"));
		return;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	TArray<FVector> UsedLocations;

	int32 SpawnCounter = 0;

	while (SpawnCounter < DesiredPowerupCount && Locations.Num() > 0)
	{
		int32 RandomLocationIndex = FMath::RandRange(0, Locations.Num() - 1);

		FVector PickedLocation = Locations[RandomLocationIndex];

		Locations.RemoveAt(RandomLocationIndex);

		bool bValidLocations = true;

		for (FVector OtherLocation : UsedLocations)
		{
			float DistanceTo = (PickedLocation - OtherLocation).Size();

			if (DistanceTo < RequiredPowerupDistance)
			{
				DrawDebugSphere(GetWorld(), PickedLocation, 50.0f, 20, FColor::Red, false, 10.0f);
				bValidLocations = false;
				UE_LOG(LogTemp, Log, TEXT("Distance too short to spawn pickup."));
				break;
				
			}
		}
		if (!bValidLocations)
		{
			continue;
		}

		int32 RandomClassIndex = FMath::RandRange(0, PickupClasses.Num() - 1);
		TSubclassOf<AActor> RandomPickupClass = PickupClasses[RandomClassIndex];

		GetWorld()->SpawnActor<AActor>(RandomPickupClass, PickedLocation, FRotator::ZeroRotator);

		UsedLocations.Add(PickedLocation);
		SpawnCounter++;
		UE_LOG(LogTemp, Log, TEXT("Found %i Pickups."), SpawnCounter);
		
	}
}

void AHMP_GameModeBase::RespawnPlayerElapsed(AController* Controller)
{
	if (ensure(Controller))
	{
		Controller->UnPossess();
		
		RestartPlayer(Controller);
		}
}

void AHMP_GameModeBase::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
	AHMP_PlayerCharacter* Player = Cast<AHMP_PlayerCharacter>(VictimActor);
	if (Player)
	{
		FTimerHandle TimerHandle_RespawnDelay;

		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());

		float RespawnDelay = 2.0f;
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnDelay, false);
	}


	AHMP_PlayerCharacter* KillingPlayer = Cast<AHMP_PlayerCharacter>(Killer);
	if (KillingPlayer)
	{
		if (AHMP_PlayerState* PS = KillingPlayer->GetPlayerState<AHMP_PlayerState>())
		{
			PS->AddCredits(CreditsToGrantOnKill);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("OnActorKilled: Victim: %s, Killer: %s"), *GetNameSafe(VictimActor), *GetNameSafe(Killer));
}


void AHMP_GameModeBase::WriteSaveGame()
{

	for (int32 i = 0; i < GameState->PlayerArray.Num(); i++)
	{
		AHMP_PlayerState* PS = Cast<AHMP_PlayerState>(GameState->PlayerArray[i]);
		if (PS)
		{
			PS->SavePlayerState(CurrentSaveGame);
			break; //single player only at this point.
		}
	}
	UGameplayStatics::SaveGameToSlot(CurrentSaveGame, SlotName, 0);
}

void AHMP_GameModeBase::LoadSaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		CurrentSaveGame = Cast<UHMP_SaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
		if (CurrentSaveGame == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load SaveGame Data."));
			return;
		}

		UE_LOG(LogTemp, Warning, TEXT("Loaded SaveGame Data."));
	}
	else
	{
		CurrentSaveGame = Cast<UHMP_SaveGame>(UGameplayStatics::CreateSaveGameObject(UHMP_SaveGame::StaticClass()));
		UE_LOG(LogTemp, Warning, TEXT("Created New SaveGame Data."));
	}
}
