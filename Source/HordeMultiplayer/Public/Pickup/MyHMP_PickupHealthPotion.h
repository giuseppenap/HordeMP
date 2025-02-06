// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup/HMP_PickupBase.h"
#include "MyHMP_PickupHealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class HORDEMULTIPLAYER_API AMyHMP_PickupHealthPotion : public AHMP_PickupBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	float HealAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	float InactivationTime;

	FTimerHandle InactivateTimer;

	FTimerHandle ActivationTimer;

	
	UFUNCTION()
	void Interact_Implementation(APawn* InstigatorPawn) override;

	UFUNCTION()
	void InactivatePickup();

	UFUNCTION()
	void ReactivatePickup();
	
};
