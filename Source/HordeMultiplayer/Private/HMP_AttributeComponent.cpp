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
	if (Health >= 0.0f)
	{
		Health += Delta;
		Health = FMath::Clamp(Health, 0.0f, MaxHealth);
		OnHealthChanged.Broadcast(nullptr, this, Health, Delta, MaxHealth);
        return true;
	}
	return false;
}



