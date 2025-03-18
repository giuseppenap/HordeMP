// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_ActionEffect_Thorns.h"

#include "HMP_AttributeComponent.h"
#include "HMP_GameplayFunctionLibrary.h"


UHMP_ActionEffect_Thorns::UHMP_ActionEffect_Thorns()
{
	ReflectFraction = 0.4f;

	Period = 0.0f;
	Duration = 0.0f;
}

void UHMP_ActionEffect_Thorns::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	UHMP_AttributeComponent* AttributeComp = UHMP_AttributeComponent::GetAttributes(GetOwningComponent()->GetOwner());
	if (AttributeComp)
	{
		AttributeComp->OnHealthChanged.AddDynamic(this, &UHMP_ActionEffect_Thorns::OnHealthChanged);
	}
	
}

void UHMP_ActionEffect_Thorns::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);

	UHMP_AttributeComponent* AttributeComp = UHMP_AttributeComponent::GetAttributes(GetOwningComponent()->GetOwner());
	if (AttributeComp)
	{
		AttributeComp->OnHealthChanged.RemoveDynamic(this, &UHMP_ActionEffect_Thorns::OnHealthChanged);
	}
	
}

void UHMP_ActionEffect_Thorns::OnHealthChanged(AActor* InstigatorActor, UHMP_AttributeComponent* OwningComp,
	float NewHealth, float Delta)
{
	AActor* OwningActor = GetOwningComponent()->GetOwner();

	// Damage Only
	if (Delta < 0.0f && OwningActor != InstigatorActor)
	{
		// Round to nearest to avoid 'ugly' damage numbers and tiny reflections
		int32 ReflectedAmount = FMath::RoundToInt(Delta * ReflectFraction);
		if (ReflectedAmount == 0)
		{
			return;
		}

		// Flip to positive, so we don't end up healing ourselves when passed into damage
		ReflectedAmount = FMath::Abs(ReflectedAmount);

		// Return damage sender...
		UHMP_GameplayFunctionLibrary::ApplyDamage(OwningActor, InstigatorActor, ReflectedAmount);
	}
}