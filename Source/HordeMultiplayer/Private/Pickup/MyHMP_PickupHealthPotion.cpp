// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup/MyHMP_PickupHealthPotion.h"

#include "HMP_AttributeComponent.h"
#include "NiagaraComponent.h"

AMyHMP_PickupHealthPotion::AMyHMP_PickupHealthPotion()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);

	MeshVFX = CreateDefaultSubobject<UNiagaraComponent>("MeshVFX");
	MeshVFX->SetupAttachment(RootComponent);
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
			HideAndCooldownPowerup();
		}
	}
}


