// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HMP_Action.h"
#include "NiagaraComponent.h"
#include "Pickup/HMP_PickupBase.h"
#include "HMP_GrantEffectPickup.generated.h"

/**
 * 
 */
UCLASS()
class HORDEMULTIPLAYER_API AHMP_GrantEffectPickup : public AHMP_PickupBase
{
	GENERATED_BODY()


protected:

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	UNiagaraComponent* MeshVFX;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	USoundBase* PickupSound;

	UPROPERTY(EditAnywhere, Category = "Powerup")
	TSubclassOf<UHMP_Action> ActionToGrant;
	
public:

	UFUNCTION()
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	AHMP_GrantEffectPickup();

	
};
