// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HMPBTTaskHealSelf.generated.h"

/**
 * 
 */
UCLASS()
class HORDEMULTIPLAYER_API UHMPBTTaskHealSelf : public UBTTaskNode
{
	GENERATED_BODY()
	
	
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	float HealingValue;
	
};
