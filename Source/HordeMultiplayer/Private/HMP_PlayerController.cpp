// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_PlayerController.h"


void AHMP_PlayerController::BeginPlayingState()
{
	BlueprintBeginPlayingState();
}

void AHMP_PlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	OnPawnChanged.Broadcast(InPawn);
}
