// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_BlackHoleProjectile.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"


void AHMP_BlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	GetWorldTimerManager().SetTimer(SpecialAttackElapsed, this, &AHMP_BlackHoleProjectile::SpecialAttack_TimerElapsed, 3.2f);
	UE_LOG(LogTemp, Warning, TEXT("BlackholeTimerStarted"));
}

void AHMP_BlackHoleProjectile::SpecialAttack_TimerElapsed()
{
	GetWorldTimerManager().ClearTimer(SpecialAttackElapsed);
	ForceComp->ForceStrength = 0;
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactVFX, GetActorLocation());
	ForceComp->FireImpulse();
	UE_LOG(LogTemp, Warning, TEXT("BlackholeTimerElapsed"));
	//Destroy();
	
	FTimerHandle AfterExplosionTimer;
	GetWorldTimerManager().SetTimer(AfterExplosionTimer, this, &AHMP_BlackHoleProjectile::AfterExplosion_TimerElapsed, 0.2f);
	
}

void AHMP_BlackHoleProjectile::AfterExplosion_TimerElapsed()
{
	Destroy();
}
