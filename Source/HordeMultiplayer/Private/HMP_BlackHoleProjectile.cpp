// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_BlackHoleProjectile.h"

#include "HMP_GameplayFunctionLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"


void AHMP_BlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	GetWorldTimerManager().SetTimer(SpecialAttackElapsed, this, &AHMP_BlackHoleProjectile::SpecialAttack_TimerElapsed, 3.2f);
	UE_LOG(LogTemp, Warning, TEXT("BlackholeTimerStarted"));
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AHMP_BlackHoleProjectile::OnActorOverlap);
}

void AHMP_BlackHoleProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TArray<AActor*> OverlappingActors;
	OverlappingActors.Add(OtherActor);

	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (OtherActor && OtherActor != GetInstigator())
		{

			// Apply Damage & Impulse
			if (UHMP_GameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OverlappingActor, Damage, SweepResult))
			{
				if (bShouldExplodeOnDamage)
				{
					Explode_Implementation();
				}

				UGameplayStatics::PlaySound2D(this, EnemyHitSound, 1, 1, 0);
			}
		}
	}
	
}

void AHMP_BlackHoleProjectile::SpecialAttack_TimerElapsed()
{
	GetWorldTimerManager().ClearTimer(SpecialAttackElapsed);
	ForceComp->ForceStrength = 0;
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactVFX, GetActorLocation());
	ForceComp->FireImpulse();
	UGameplayStatics::PlaySoundAtLocation(this, HitSoundBase, GetActorLocation(), GetActorRotation(), 0.1f, 1.0f, 0.0f, AttenuationProjectile);
	UE_LOG(LogTemp, Warning, TEXT("BlackholeTimerElapsed"));
	//Destroy();
	
	FTimerHandle AfterExplosionTimer;
	GetWorldTimerManager().SetTimer(AfterExplosionTimer, this, &AHMP_BlackHoleProjectile::AfterExplosion_TimerElapsed, 0.2f);
	
}

void AHMP_BlackHoleProjectile::AfterExplosion_TimerElapsed()
{
	Destroy();
}
