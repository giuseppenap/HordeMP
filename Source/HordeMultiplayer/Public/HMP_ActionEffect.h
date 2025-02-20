// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HMP_Action.h"
#include "HMP_ActionEffect.generated.h"

/**
 * 
 */
UCLASS()
class HORDEMULTIPLAYER_API UHMP_ActionEffect : public UHMP_Action
{
	GENERATED_BODY()

public:

	
	void StartAction_Implementation(AActor* Instigator) override;

	
	void StopAction_Implementation(AActor* Instigator) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Effect)
	float Duration;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Effect)
	float Period;


	FTimerHandle PeriodHandle;
	FTimerHandle DurationHandle;

	UFUNCTION(BlueprintNativeEvent, Category = Effect)
	void ExecutePeriodicEffect(AActor* Instigator);

	UHMP_ActionEffect();
	
};
