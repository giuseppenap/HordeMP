// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_ActionComponent.h"
#include "HMP_Action.h"


UHMP_ActionComponent::UHMP_ActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHMP_ActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<UHMP_Action> ActionClass : DefaultActions)
	{
		AddAction(ActionClass);
	}
}


// Called every frame
void UHMP_ActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UHMP_ActionComponent::AddAction(TSubclassOf<UHMP_Action> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	UHMP_Action* NewAction = NewObject<UHMP_Action>(this, ActionClass);
	if (NewAction)
	{
		Actions.Add(NewAction);
	}
}

bool UHMP_ActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for (UHMP_Action* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
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
			Action->StopAction(Instigator);
			return true;
		}
	}
	return false;	
}
