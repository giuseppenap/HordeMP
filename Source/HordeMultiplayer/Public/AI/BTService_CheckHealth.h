// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTService_CheckHealth.generated.h"

/**
 * 
 */
UCLASS()
class HORDEMULTIPLAYER_API UBTService_CheckHealth : public UBTService_BlueprintBase
{
	GENERATED_BODY()

protected:

	/*
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector HealthUnderTresholdKey;

	UPROPERTY(EditAnywhere, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float HealthLimit;

	UBTService_CheckHealth();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	*/
	
};
