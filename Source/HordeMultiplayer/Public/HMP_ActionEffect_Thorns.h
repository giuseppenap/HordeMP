// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HMP_ActionEffect.h"
#include "HMP_AttributeComponent.h"
#include "HMP_ActionEffect_Thorns.generated.h"

/**
 * 
 */
UCLASS()
class HORDEMULTIPLAYER_API UHMP_ActionEffect_Thorns : public UHMP_ActionEffect
{
	GENERATED_BODY()

protected:

	float ReflectFraction;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UHMP_AttributeComponent* OwningComp, float NewHealth, float Delta);

public:

	void StartAction_Implementation(AActor* Instigator) override;
	
	void StopAction_Implementation(AActor* Instigator) override;

	UHMP_ActionEffect_Thorns();
	
};

