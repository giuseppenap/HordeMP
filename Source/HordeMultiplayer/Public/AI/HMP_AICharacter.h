// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HMP_AttributeComponent.h"
#include "GameFramework/Character.h"
#include "UI/HMP_WorldUserWidget.h"
#include "HMP_AICharacter.generated.h"

class UPawnSensingComponent;
class UUserWidget;
class UHMP_AttributeComponent;
class UHMP_ActionComponent;
class USoundBase;
class USoundAttenuation;

UCLASS()
class HORDEMULTIPLAYER_API AHMP_AICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHMP_AICharacter();

protected:

	/* Key for AI Blackboard 'TargetActor' */
	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TargetActorKey;

	UPROPERTY(BlueprintReadOnly)
	UHMP_WorldUserWidget* ActiveHealthBar;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	USoundBase* DeathSoundClass;

	/* Widget to display when bot first sees a player. */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> SpottedWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	USoundAttenuation* AttenuationDeath;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimeToHitParameter;

	UFUNCTION()
	void SetTargetActor(AActor* NewTarget);
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Components")
	UHMP_AttributeComponent* AttributeComp;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Components")
	UHMP_ActionComponent* ActionComp;

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION(BlueprintCallable, Category = "AI")
	AActor* GetTargetActor() const;

	UFUNCTION()
	void OnHealthChangedImplementation(AActor* InstigatorActor, UHMP_AttributeComponent* OwningComp, float NewHealth, float Delta);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastPawnSeen();
	

};

