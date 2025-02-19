// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HMP_Action.generated.h"

class UWorld;
/**
 * 
 */
UCLASS(Blueprintable)
class HORDEMULTIPLAYER_API UHMP_Action : public UObject
{
	GENERATED_BODY()

public:


	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StopAction(AActor* Instigator);

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;

	UWorld* GetWorld() const override;
	
};
