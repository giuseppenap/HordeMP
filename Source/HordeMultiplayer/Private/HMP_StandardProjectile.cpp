// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_StandardProjectile.h"

#include "HMP_GameplayFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AHMP_StandardProjectile::AHMP_StandardProjectile()
{
	Damage = 20;
}

void AHMP_StandardProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AHMP_StandardProjectile::OnActorOverlap);
}


void AHMP_StandardProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{

		UHMP_ActionComponent* ActionComp = Cast<UHMP_ActionComponent>(OtherActor->GetComponentByClass(UHMP_ActionComponent::StaticClass()));

		if (ActionComp && ActionComp->ActiveGameplayTags.HasTag(ParryTag))
		{
			UGameplayStatics::PlaySoundAtLocation(this, EffectSound, GetActorLocation(), GetActorRotation(), 0.1f, 1.0f, 0.0f, AttenuationEffect);
			MovementComp->Velocity = -MovementComp->Velocity;

			SetInstigator(Cast<APawn>(OtherActor));
			return;
		}

		// Apply Damage & Impulse
		if (UHMP_GameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, Damage, SweepResult))
		{
			if (bShouldExplodeOnDamage)
			{
				Explode_Implementation();
			}

			UGameplayStatics::PlaySound2D(this, EnemyHitSound, 1, 1, 0);

			if (ActionComp && EffectActionClass && HasAuthority())
			{
				ActionComp->AddAction(GetInstigator(), EffectActionClass);
			}
		}
	}
}
