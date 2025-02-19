// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_PlayerState.h"

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
