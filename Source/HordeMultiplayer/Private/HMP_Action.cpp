// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_Action.h"
#include "HMP_ActionComponent.h"
#include "HordeMultiplayer/HordeMultiplayer.h"
#include "Net/UnrealNetwork.h"




void UHMP_Action::Initialize(UHMP_ActionComponent* NewActionComp)
{
	ActionComp = NewActionComp;
}

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
	//LogOnScreen(this, FString::Printf(TEXT("Started: %s"), *ActionName.ToString()), FColor::Green);

	UHMP_ActionComponent* Comp = GetOwningComponent();

	Comp->ActiveGameplayTags.AppendTags(GrantedTags);

	RepData.bIsRunning = true;
	RepData.Instigator = Instigator;
}

void UHMP_Action::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopped: %s"), *GetNameSafe(this));
	//LogOnScreen(this, FString::Printf(TEXT("Stopped: %s"), *ActionName.ToString()), FColor::White);

	//ensureAlways(bIsRunning);

	UHMP_ActionComponent* Comp = GetOwningComponent();

	Comp->ActiveGameplayTags.RemoveTags(GrantedTags);

	RepData.bIsRunning = false;
	RepData.Instigator = Instigator;
}

UWorld* UHMP_Action::GetWorld() const
{
	// Outer is Set when creating action via NewObject<!>
	AActor* Actor = Cast<AActor>(GetOuter());
	if (Actor)
	{
		return Actor->GetWorld();
	}
	
	return nullptr;
}

UHMP_ActionComponent* UHMP_Action::GetOwningComponent() const
{
	return ActionComp;
}

void UHMP_Action::OnRep_RepData()
{
	if (RepData.bIsRunning)
	{
		StartAction(RepData.Instigator);
	}
	else
	{
		StopAction(RepData.Instigator);
	}
}



bool UHMP_Action::IsRunning() const
{
	return RepData.bIsRunning;
}

void UHMP_Action::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHMP_Action, RepData);
	DOREPLIFETIME(UHMP_Action, ActionComp);
}


