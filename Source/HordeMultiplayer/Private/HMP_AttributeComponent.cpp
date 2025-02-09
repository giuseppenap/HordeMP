// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_AttributeComponent.h"

// Sets default values for this component's properties
UHMP_AttributeComponent::UHMP_AttributeComponent()
{
	Health = 100;
	MaxHealth = 100;
}

bool UHMP_AttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}


bool UHMP_AttributeComponent::ApplyHealthChange(float Delta)
{
	float OldHealth = Health;
	
	Health = FMath::Clamp(Health + Delta, 0.0f, MaxHealth);

	float ActualDelta = Health - OldHealth;
	LastDamage = ActualDelta;
	OnHealthChanged.Broadcast(nullptr, this, Health, ActualDelta);
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




