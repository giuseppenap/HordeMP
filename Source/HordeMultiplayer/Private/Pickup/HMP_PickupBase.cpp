// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup/HMP_PickupBase.h"

#include "NiagaraComponent.h"

class UStaticMeshComponent;

// Sets default values
AHMP_PickupBase::AHMP_PickupBase()
{

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereCollision->SetCollisionProfileName("Pickup");
	RootComponent = SphereCollision;

	bReplicates = true;

}

void AHMP_PickupBase::Interact_Implementation(APawn* InstigatorPawn)
{
	
}

void AHMP_PickupBase::ShowPowerup()
{
	SetPowerupState(true);
}


void AHMP_PickupBase::HideAndCooldownPowerup()
{
	SetPowerupState(false);

	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &AHMP_PickupBase::ShowPowerup, RespawnTime);
}

void AHMP_PickupBase::SetPowerupState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);

	//Propagate Changes from the root to the children -> true variable
	RootComponent->SetVisibility(bNewIsActive, true);
}

