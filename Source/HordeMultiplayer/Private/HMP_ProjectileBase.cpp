// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_ProjectileBase.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "UObject/FastReferenceCollector.h"


// Sets default values
AHMP_ProjectileBase::AHMP_ProjectileBase()
{
 	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this, &AHMP_ProjectileBase::OnActorHit);
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
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

}

void AHMP_ProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void AHMP_ProjectileBase::Explode_Implementation()
{
	if (ensure(!IsPendingKillPending()))
	{
		ForceComp->FireImpulse();
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactVFX, GetActorLocation());

		Destroy();
	}
}

void AHMP_ProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}



