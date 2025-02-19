// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_ProjectileBase.h"

#include "HMP_AttributeComponent.h"
#include "HMP_GameplayFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"



// Sets default values
AHMP_ProjectileBase::AHMP_ProjectileBase()
{
 	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");

	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UNiagaraComponent>("EffectComp");
	EffectComp->SetupAttachment(RootComponent);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.0f;
	MovementComp->InitialSpeed = 8000.0f;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(SphereComp);
	ForceComp->bImpulseVelChange = true;
	ForceComp->Radius = 200.0f;
	ForceComp->ImpulseStrength = 400.0f;
	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);

	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	AudioComp->SetupAttachment(RootComponent);
	AudioComp->SetVolumeMultiplier(0.1f);
	

}

void AHMP_ProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AudioComp->FadeIn(0.5f);
	SphereComp->OnComponentHit.AddDynamic(this, &AHMP_ProjectileBase::OnActorHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AHMP_ProjectileBase::OnActorOverlap);
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}

void AHMP_ProjectileBase::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		if (UHMP_GameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, Damage, SweepResult))
		{
			Explode_Implementation();
			// @Fixme: 
			/*APlayerController* PC = UGameplayStatics::GetPlayerController(GetInstigator(), 0);
			if (PC && ImpactCameraShake)
			{
				PC->ClientStartCameraShake(ImpactCameraShake);	
			}
			UHMP_AttributeComponent* AttributeComp = UHMP_AttributeComponent::GetAttributes(OtherActor);
			if (AttributeComp->IsAlive())
			{
				UGameplayStatics::PlaySoundAtLocation(this, EnemyKilledSound, GetActorLocation(), GetActorRotation(), 0.1f, 1.0f, 0.0f, AttenuationProjectile);
			}
			UGameplayStatics::PlaySoundAtLocation(this, EnemyHitSound, GetActorLocation(), GetActorRotation(), 0.1f, 1.0f, 0.0f, AttenuationProjectile);
			Explode_Implementation();
			AudioComp->FadeOut(0.6f,1);
			UGameplayStatics::PlaySoundAtLocation(this, HitSoundBase, GetActorLocation(), GetActorRotation(), 0.1f, 1.0f, 0.0f, AttenuationProjectile);*/
		}
	}
}

void AHMP_ProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != GetInstigator())
	{
		Explode();
	}
}

void AHMP_ProjectileBase::Explode_Implementation()
{
	if (ensure(!IsPendingKillPending()))
	{
		ForceComp->FireImpulse();
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactVFX, GetActorLocation());
		AudioComp->FadeOut(0.6f,1);
		UGameplayStatics::PlaySoundAtLocation(this, HitSoundBase, GetActorLocation(), GetActorRotation(), 0.1f, 1.0f, 0.0f, AttenuationProjectile);

		Destroy();
	}
}




