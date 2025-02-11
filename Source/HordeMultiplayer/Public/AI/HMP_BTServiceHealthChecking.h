// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "HMP_BTServiceHealthChecking.generated.h"

/**
 * 
 */
UCLASS()
class HORDEMULTIPLAYER_API UHMP_BTServiceHealthChecking : public UBTService
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector HealthUnderTresholdKey;

	UPROPERTY(EditAnywhere, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float HealthLimit;

	void UHMP_BTService_HealthChecking();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	
};
