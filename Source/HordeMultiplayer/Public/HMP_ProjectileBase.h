// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "HMP_ProjectileBase.generated.h"

class USphereComponent;
class UNiagaraComponent;
class UProjectileMovementComponent;
class URadialForceComponent;
class UAudioComponent;
class USoundAttenuation;
class USoundBase;

UCLASS()
class HORDEMULTIPLAYER_API AHMP_ProjectileBase : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UNiagaraSystem* ImpactVFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UNiagaraComponent* EffectComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	URadialForceComponent* ForceComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UAudioComponent* AudioComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	USoundCue* HitSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	USoundBase* HitSoundBase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects")
	USoundAttenuation* AttenuationProjectile;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	//virtual so it can be overriden in child classes
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();

	virtual void PostInitializeComponents() override;
	
public:	
	// Sets default values for this actor's properties
	AHMP_ProjectileBase();

};
