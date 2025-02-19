// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_AttributeComponent.h"

#include "HMP_GameModeBase.h"


static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("hmp.DamageMultiplier"), 1.0f, TEXT("Global Damage Modifier for Attribute Component."), ECVF_Cheat);

// Sets default values for this component's properties
UHMP_AttributeComponent::UHMP_AttributeComponent()
{
	Health = 100;
	MaxHealth = 100;
}

bool UHMP_AttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -MaxHealth);
}

bool UHMP_AttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}


bool UHMP_AttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged() && Delta <= 0.0f)
	{
		return false;
	}

	if (Delta <= 0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();

		Delta *= DamageMultiplier;
	}
	
	float OldHealth = Health;
	
	Health = FMath::Clamp(Health + Delta, 0.0f, MaxHealth);

	float ActualDelta = Health - OldHealth;
	LastDamage = ActualDelta;
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);

	if (ActualDelta < 0.0f && Health == 0.0f)
	{
		AHMP_GameModeBase* GM = GetWorld()->GetAuthGameMode<AHMP_GameModeBase>();
		if (GM)
		{
			GM->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}
    return ActualDelta != 0;
}

float UHMP_AttributeComponent::GetHealth() const
{
	return Health;
}

bool UHMP_AttributeComponent::IsFullHealth() const
{
	return Health == MaxHealth;
}

float UHMP_AttributeComponent::GetMaxHealth() const
{
	return MaxHealth;
}

float UHMP_AttributeComponent::GetLastDamage() const
{
	return LastDamage;
}

UHMP_AttributeComponent* UHMP_AttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<UHMP_AttributeComponent>(FromActor->GetComponentByClass(UHMP_AttributeComponent::StaticClass()));
	}

	return nullptr;
}

bool UHMP_AttributeComponent::IsActorAlive(AActor* Actor)
{
	UHMP_AttributeComponent* AttributeComp = GetAttributes(Actor);
	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}
	
	return false;
}



