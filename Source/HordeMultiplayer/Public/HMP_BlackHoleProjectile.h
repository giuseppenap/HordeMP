// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HMP_ProjectileBase.h"
#include "HMP_BlackHoleProjectile.generated.h"

/**
 * 
 */
UCLASS()
class HORDEMULTIPLAYER_API AHMP_BlackHoleProjectile : public AHMP_ProjectileBase
{
	GENERATED_BODY()

protected:
	FTimerHandle SpecialAttackElapsed;

public:
	void BeginPlay() override;

protected:

	UFUNCTION()
	void SpecialAttack_TimerElapsed();

	UFUNCTION()
	void AfterExplosion_TimerElapsed();
	
};
