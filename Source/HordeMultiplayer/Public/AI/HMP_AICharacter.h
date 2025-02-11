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

UCLASS()
class HORDEMULTIPLAYER_API AHMP_AICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHMP_AICharacter();

protected:

	UPROPERTY(BlueprintReadOnly)
	UHMP_WorldUserWidget* ActiveHealthBar;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimeToHitParameter;

	UFUNCTION()
	void SetTargetActor(AActor* NewTarget);
	
	UPROPERTY(VisibleAnywhere)
	UHMP_AttributeComponent* AttributeComp;

	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
	void OnHealthChangedImplementation(AActor* InstigatorActor, UHMP_AttributeComponent* OwningComp, float NewHealth, float Delta);
	

};
