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



public:
	void BeginPlay() override;

protected:

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SpecialAttack_TimerElapsed();

	UFUNCTION()
	void AfterExplosion_TimerElapsed();

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float Damage;

	FTimerHandle SpecialAttackElapsed;
	
};
