// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup/HMP_PickupBase.h"
#include "MyHMP_PickupHealthPotion.generated.h"


class UNiagaraComponent;

/**
 * 
 */
UCLASS()
class HORDEMULTIPLAYER_API AMyHMP_PickupHealthPotion : public AHMP_PickupBase
{
	GENERATED_BODY()

public:

	AMyHMP_PickupHealthPotion();
	

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	UNiagaraComponent* MeshVFX;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	USoundBase* PickupSound;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	float HealAmount;

	FTimerHandle InactivateTimer;

	FTimerHandle ActivationTimer;

	
	UFUNCTION()
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	
	
};
