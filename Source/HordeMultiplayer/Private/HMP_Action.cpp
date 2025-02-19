// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_Action.h"

void UHMP_Action::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));
}

void UHMP_Action::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped: %s"), *GetNameSafe(this));
}

UWorld* UHMP_Action::GetWorld() const
{
	// Outer is Set when creating action via NewObject<!>
	UActorComponent* Comp = Cast<UActorComponent>(GetOuter());
	if (Comp)
	{
		return Comp->GetWorld();
	}
	
	return nullptr;
}
