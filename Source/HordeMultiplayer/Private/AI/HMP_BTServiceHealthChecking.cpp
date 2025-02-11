// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HMP_BTServiceHealthChecking.h"

#include "AIController.h"
#include "HMP_AttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void UHMP_BTServiceHealthChecking::UHMP_BTService_HealthChecking()
{
	HealthLimit = 0.3f;
}

void UHMP_BTServiceHealthChecking::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//Check if Health is low

	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ensure(AIPawn))
	{
		UHMP_AttributeComponent* AttributeComp = UHMP_AttributeComponent::GetAttributes(AIPawn);;
		if (ensure(AttributeComp))
		{
			bool bUnderHealthTreshold = (AttributeComp->GetHealth() / AttributeComp->GetMaxHealth()) < HealthLimit;

			UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
			BlackboardComp->SetValueAsBool(HealthUnderTresholdKey.SelectedKeyName, bUnderHealthTreshold);
			//UE_LOG(LogTemp, Warning, TEXT(" Bool Value is_ %s "), bUnderHealthTreshold? "true" : "false");
		}
	}
}
