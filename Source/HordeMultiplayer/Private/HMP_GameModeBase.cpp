// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_GameModeBase.h"

#include "EngineUtils.h"
#include "AI/HMP_AICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"


AHMP_GameModeBase::AHMP_GameModeBase()
{
	SpawnTimerInterval = 2.0f;
}

void AHMP_GameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &AHMP_GameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}


void AHMP_GameModeBase::SpawnBotTimerElapsed()
{

	int32 NrOfAliveBots = 0;
	for (AHMP_AICharacter* Bot:TActorRange<AHMP_AICharacter>(GetWorld()))
	{
		UHMP_AttributeComponent* AttributeComp = Cast<UHMP_AttributeComponent>(Bot->GetComponentByClass(UHMP_AttributeComponent::StaticClass()));
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
	QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AHMP_GameModeBase::OnQueryCompleted);
	}
}

void AHMP_GameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
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
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);

		DrawDebugSphere(GetWorld(), Locations[0], 50.0f, 30, FColor::Blue, false, 60.0f	);
	}
}

