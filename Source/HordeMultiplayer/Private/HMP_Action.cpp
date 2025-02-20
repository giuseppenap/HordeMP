// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_Action.h"
#include "HMP_ActionComponent.h"
bool UHMP_Action::CanStart_Implementation(AActor* Instigator)
{
	if (IsRunning())
	{
		return false;
	}
	
	UHMP_ActionComponent* Comp = GetOwningComponent();

	if (Comp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}
	return true;
}

void UHMP_Action::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));

	UHMP_ActionComponent* Comp = GetOwningComponent();

	Comp->ActiveGameplayTags.AppendTags(GrantedTags);

	bIsRunning = true;
}

void UHMP_Action::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped: %s"), *GetNameSafe(this));

	ensureAlways(bIsRunning);

	UHMP_ActionComponent* Comp = GetOwningComponent();

	Comp->ActiveGameplayTags.RemoveTags(GrantedTags);

	bIsRunning = false;
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

UHMP_ActionComponent* UHMP_Action::GetOwningComponent() const
{
	return Cast<UHMP_ActionComponent>(GetOuter());
}

bool UHMP_Action::IsRunning() const
{
	return bIsRunning;
}

