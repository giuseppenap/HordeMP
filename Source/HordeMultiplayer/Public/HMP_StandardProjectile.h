// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HMP_ProjectileBase.h"
#include "HMP_StandardProjectile.generated.h"

/**
 * 
 */
UCLASS()
class HORDEMULTIPLAYER_API AHMP_StandardProjectile : public AHMP_ProjectileBase
{
	GENERATED_BODY()


protected:

	UPROPERTY(EditDefaultsOnly, Category = "Damage", meta = (OrderWithinCategory = 0))
	FGameplayTag ParryTag;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UHMP_ActionEffect> EffectActionClass;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float Damage;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	AHMP_StandardProjectile();

	virtual void PostInitializeComponents() override;
};
