// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup/MyHMP_PickupHealthPotion.h"

#include "HMP_AttributeComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"

void AMyHMP_PickupHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	Super::Interact_Implementation(InstigatorPawn);
	UHMP_AttributeComponent* AttributeComp = Cast<UHMP_AttributeComponent>(InstigatorPawn->GetComponentByClass(UHMP_AttributeComponent::StaticClass()));

	if (AttributeComp)
	{
		float CurrentHealth = AttributeComp->GetHealth();
		float MaxHealth = AttributeComp->GetMaxHealth();
			if (MaxHealth > CurrentHealth)
			{
				Mesh->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->GetTimeSeconds());
				AttributeComp->ApplyHealthChange(HealAmount);
				GetWorldTimerManager().SetTimer(InactivateTimer, this, &AMyHMP_PickupHealthPotion::ReactivatePickup, InactivationTime);
				GetWorldTimerManager().SetTimer(ActivationTimer, this, &AMyHMP_PickupHealthPotion::InactivatePickup, 0.5f);
			}
	}
}

void AMyHMP_PickupHealthPotion::InactivatePickup()
{
	Mesh->SetVisibility(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (MeshVFX)
	{
		MeshVFX->SetVisibility(false);
		MeshVFX->Deactivate();
	}
	
}

void AMyHMP_PickupHealthPotion::ReactivatePickup()
{
	Mesh->SetVisibility(true);
	Mesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	if (MeshVFX)
	{
		MeshVFX->SetVisibility(true);
		MeshVFX->Activate();
	}

}
