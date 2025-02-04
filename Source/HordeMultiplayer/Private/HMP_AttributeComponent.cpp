// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_AttributeComponent.h"

// Sets default values for this component's properties
UHMP_AttributeComponent::UHMP_AttributeComponent()
{
	Health = 100;
	
}

bool UHMP_AttributeComponent::IsAlive()
{

	return Health > 0.0f;
	
}


bool UHMP_AttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
	
}



