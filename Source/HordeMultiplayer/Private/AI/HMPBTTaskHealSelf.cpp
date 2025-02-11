// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HMPBTTaskHealSelf.h"

#include "AIController.h"
#include "HMP_AttributeComponent.h"

EBTNodeResult::Type UHMPBTTaskHealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ensure(AIPawn))
	{
		UHMP_AttributeComponent* AttributeComp = UHMP_AttributeComponent::GetAttributes(AIPawn);;
		if (ensure(AttributeComp))
		{
			
			AttributeComp->ApplyHealthChange(AIPawn, AttributeComp->GetMaxHealth() * HealingValue);
			return EBTNodeResult::Succeeded;
		}
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}
