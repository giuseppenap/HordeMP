// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup/MyHMP_PickupHealthPotion.h"

#include "HMP_AttributeComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"

AMyHMP_PickupHealthPotion::AMyHMP_PickupHealthPotion()
{
	MeshVFX = CreateDefaultSubobject<UNiagaraComponent>("MeshVFX");
	MeshVFX->SetupAttachment(RootComponent);

	bReplicates = true;
}

void AMyHMP_PickupHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	UHMP_AttributeComponent* AttributeComp = Cast<UHMP_AttributeComponent>(InstigatorPawn->GetComponentByClass(UHMP_AttributeComponent::StaticClass()));

	if (ensure(AttributeComp) && !AttributeComp->IsFullHealth())
	{
		if (AttributeComp->ApplyHealthChange(this, HealAmount))
		{
			UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation(), GetActorRotation(), 0.3, 1, 0);
			HideAndCooldownPowerup();
		}
	}
}


