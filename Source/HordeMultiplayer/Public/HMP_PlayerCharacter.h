// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HMP_AttributeComponent.h"
#include "HMP_BlackHoleProjectile.h"
#include "GameFramework/Character.h"
#include "HMP_PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHMP_InteractionComponent;
class UAnimMontage;

UCLASS()
class HORDEMULTIPLAYER_API AHMP_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere, Category = Attack)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = Attack)
	TSubclassOf<AActor> SpecialProjectileClass;

	UPROPERTY(EditAnywhere, Category = Attack)
	TSubclassOf<AActor> DashProjectileClass;

	UPROPERTY(EditAnywhere, Category = Attack)
	TSubclassOf<AActor> AlternateProjectileClass;
	
	UPROPERTY(EditAnywhere, Category = Attack)
	UAnimMontage* AttackAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHMP_AttributeComponent* AttributeComp;
	
	UPROPERTY(EditAnywhere, Category = Attack)
	UNiagaraSystem* MuzzleEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<UCameraShakeBase> ImpactCameraShake;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<UCameraShakeBase> DeathCameraShake;

	FTimerHandle TimerHandle_PrimaryAttack;

public:
	// Sets default values for this character's properties
	AHMP_PlayerCharacter();

protected:

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UHMP_InteractionComponent* InteractionComp;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void PrimaryAttack();

	UFUNCTION()
	void PrimaryInteract();

	UFUNCTION()
    void SpecialAttack();

	UFUNCTION()
	void Dash();

	UFUNCTION()
	void AlternateFire();
	
	UFUNCTION()
	void PrimaryAttack_TimeElapsed();

	UFUNCTION()
	void SpecialAttack_TimeElapsed();

	UFUNCTION()
	void Dash_TimeElapsed();

	UFUNCTION()
	void AlternateFire_TimeElapsed();
	
	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UHMP_AttributeComponent* OwningComp, float NewHealth, float Delta, float MaxHealth);


	UFUNCTION()
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
