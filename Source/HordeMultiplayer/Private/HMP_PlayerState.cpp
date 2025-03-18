// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_PlayerState.h"

#include "Net/UnrealNetwork.h"

void AHMP_PlayerState::OnRep_Credits(int32 OldCredits)
{
	OnCreditsChanged.Broadcast(this, Credits, Credits - OldCredits);
}

int32 AHMP_PlayerState::GetCredits() const
{
	UE_LOG(LogTemp, Warning, TEXT("%i"), Credits);
	return Credits;
}

void AHMP_PlayerState::AddCredits(int32 Delta)
{
	if (!ensure(Delta > 0.0f))
	{
		return;	
	}
	
	Credits += Delta;

	OnCreditsChanged.Broadcast(this, Credits, Delta);
	UE_LOG(LogTemp, Warning, TEXT("%i"), Credits);
}

bool AHMP_PlayerState::RemoveCredits(int32 Delta)
{
	if (Credits < Delta)
	{
		return false;
	}

	Credits -= Delta;

	OnCreditsChanged.Broadcast(this, Credits, -Delta);

	return true;

}

void AHMP_PlayerState::SavePlayerState_Implementation(UHMP_SaveGame* SaveObject)
{
	if (SaveObject)
	{
		SaveObject->Credits = Credits;
	}
}

void AHMP_PlayerState::LoadPlayerState_Implementation(UHMP_SaveGame* SaveObject)
{
	if (SaveObject)
	{
		//Credits = SaveObject->Credits;
		AddCredits(SaveObject->Credits);
	}
}

void AHMP_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHMP_PlayerState, Credits);
}
