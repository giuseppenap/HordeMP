// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HMP_AttributeComponent.h"
#include "GameFramework/Character.h"
#include "HMP_AICharacter.generated.h"

class UPawnSensingComponent;

UCLASS()
class HORDEMULTIPLAYER_API AHMP_AICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHMP_AICharacter();

protected:

	/*UPROPERTY(VisibleAnywhere)
	UHMP_AttributeComponent* AttributeComp;*/

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	/*UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UHMP_AttributeComponent* OwningComp, float NewHealth, float Delta, float MaxHealth);*/
	

};
