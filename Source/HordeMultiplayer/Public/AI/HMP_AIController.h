// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HMP_AIController.generated.h"

/**
 * 
 */
UCLASS()
class HORDEMULTIPLAYER_API AHMP_AIController : public AAIController
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category= "AI")
	UBehaviorTree* BehaviorTree;
	
	virtual void BeginPlay() override;
	
};
