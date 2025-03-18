// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup/HMP_PickupBase.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AHMP_PickupBase::AHMP_PickupBase()
{

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereCollision->SetCollisionProfileName("Pickup");
	RootComponent = SphereCollision;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);

	bIsActive = true;
	RespawnTime = 10.0f;

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
	bIsActive = bNewIsActive;
	OnRep_IsActive();
}

void AHMP_PickupBase::OnRep_IsActive()
{
	SetActorEnableCollision(bIsActive);
    
    //Propagate Changes from the root to the children -> true variable
	RootComponent->SetVisibility(bIsActive, true);
}

void AHMP_PickupBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHMP_PickupBase, bIsActive);
}