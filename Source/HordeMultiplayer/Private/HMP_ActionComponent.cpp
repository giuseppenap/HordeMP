// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_ActionComponent.h"
#include "HMP_Action.h"


UHMP_ActionComponent::UHMP_ActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}



// Called when the game starts
void UHMP_ActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<UHMP_Action> ActionClass : DefaultActions)
	{
		AddAction(GetOwner(), ActionClass);
	}
}


// Called every frame
void UHMP_ActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString DebugMsg = GetNameSafe(GetOwner()) + " : " + ActiveGameplayTags.ToStringSimple(); 
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::White, DebugMsg);
}


void UHMP_ActionComponent::AddAction(AActor* Instigator, TSubclassOf<UHMP_Action> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	UHMP_Action* NewAction = NewObject<UHMP_Action>(this, ActionClass);
	if (ensure(NewAction))
	{
		Actions.Add(NewAction);

		if (NewAction->bAutoStart && ensure(NewAction->CanStart(Instigator)))
		{
			NewAction->StartAction(Instigator);
		}
	}
}

void UHMP_ActionComponent::RemoveAction(UHMP_Action* ActionToRemove)
{
	if (!ensure(ActionToRemove && !ActionToRemove->IsRunning()))
	{
		return;
	}
	
	Actions.Remove(ActionToRemove);
}

bool UHMP_ActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for (UHMP_Action* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (!Action->CanStart(Instigator))
			{
				FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *ActionName.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);
				continue;
			}

			// Is Client?
			if (!GetOwner()->HasAuthority())
			{
				ServerStartAction(Instigator, ActionName);
			}
			
			Action->StartAction(Instigator);
			return true;
		}
	}
	return false;
}

bool UHMP_ActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for (UHMP_Action* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			if (Action->IsRunning())
			{
			Action->StopAction(Instigator);
			return true;
			}
		}
	}
	return false;	
}

void UHMP_ActionComponent::ServerStartAction_Implementation(AActor* Instigator, FName ActionName)
{
	StartActionByName(Instigator, ActionName);
}
