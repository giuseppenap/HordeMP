// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HMP_ActionComponent.h"
#include "HMP_AttributeComponent.h"
#include "GameFramework/Character.h"
#include "HMP_PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHMP_InteractionComponent;
class UHMP_ActionComponent;

UCLASS()
class HORDEMULTIPLAYER_API AHMP_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<UCameraShakeBase> ImpactCameraShake;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<UCameraShakeBase> DeathCameraShake;


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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHMP_AttributeComponent* AttributeComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHMP_ActionComponent* ActionComp;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void SprintStart();

	UFUNCTION()
	void SprintStop();

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
	void OnHealthChanged(AActor* InstigatorActor, UHMP_AttributeComponent* OwningComp, float NewHealth, float Delta);
	
	
	virtual FVector GetPawnViewLocation() const override;
	
public:
	
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Exec)
	void HealSelf(float Amount = 100);

};
