// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup/HMP_GrantEffectPickup.h"

#include "HMP_Action.h"
#include "HMP_ActionComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"


class UHMP_ActionComponent;

AHMP_GrantEffectPickup::AHMP_GrantEffectPickup()
{
	MeshVFX = CreateDefaultSubobject<UNiagaraComponent>("MeshVFX");
	MeshVFX->SetupAttachment(RootComponent);

	bReplicates = true;
}


void AHMP_GrantEffectPickup::Interact_Implementation(APawn* InstigatorPawn)
{
	// Make sure we have instigator & that action class was set up
	if (!ensure(InstigatorPawn && ActionToGrant))
	{
		return;
	}

	UHMP_ActionComponent* ActionComp = Cast<UHMP_ActionComponent>(InstigatorPawn->GetComponentByClass(UHMP_ActionComponent::StaticClass()));
	// Check if Player already has action class
	if (ActionComp)
	{
		if (ActionComp->GetAction(ActionToGrant))
		{
			//UE_LOG(LogTemp, Log, TEXT("Instigator already has action of class: %s"), *GetNameSafe(ActionToGrant));
			FString DebugMsg = FString::Printf(TEXT("Action '%s' already known."), *GetNameSafe(ActionToGrant));
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, DebugMsg);
			return;
		}

		// Give new Ability
		ActionComp->AddAction(InstigatorPawn, ActionToGrant);
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation(), GetActorRotation(), 0.3, 1, 0);
		HideAndCooldownPowerup();
	}
}