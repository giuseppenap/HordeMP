// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_ProjectileBase.h"

#include "HMP_AttributeComponent.h"
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
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AHMP_ProjectileBase::OnActorOverlap);
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

void AHMP_ProjectileBase::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		UHMP_AttributeComponent* AttributeComp = Cast<UHMP_AttributeComponent>(OtherActor->GetComponentByClass(UHMP_AttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-20.0f);
			Explode_Implementation();
		}
	}
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



