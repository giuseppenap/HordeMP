// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HMP_AICharacter.h"

#include "BrainComponent.h"
#include "AI/HMP_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HMP_AttributeComponent.h"
#include "Perception/PawnSensingComponent.h"


// Sets default values
AHMP_AICharacter::AHMP_AICharacter()
{

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AttributeComp = CreateDefaultSubobject<UHMP_AttributeComponent>("AttributeComp");
	
}



void AHMP_AICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AHMP_AICharacter::OnPawnSeen);
	
	AttributeComp->OnHealthChanged.AddDynamic(this, &AHMP_AICharacter::OnHealthChangedImplementation);
}



void AHMP_AICharacter::OnHealthChangedImplementation(AActor* InstigatorActor, UHMP_AttributeComponent* OwningComp, float NewHealth,
	float Delta)
{
	if (Delta < 0.0f)
	{
		if (InstigatorActor != this)
		{
			SetTargetActor(InstigatorActor);
			if (NewHealth <= 0.0f)
			{
				// stop BT
				AAIController* AIC = Cast<AAIController>(GetController());
				if (AIC)
				{
					AIC->GetBrainComponent()->StopLogic("Killed");
				}
			
				// ragdoll
				GetMesh()->SetAllBodiesSimulatePhysics(true);
				GetMesh()->SetCollisionProfileName("Ragdoll");
			
				// set lifespan
				SetLifeSpan(10.0f);
			}

			USkeletalMeshComponent* SKMesh = GetMesh();
			SKMesh->SetScalarParameterValueOnMaterials("HitFlashTime", GetWorld()->GetTimeSeconds());
		}
	}
}

void AHMP_AICharacter::SetTargetActor(AActor* NewTarget)
{
	AAIController* AIC = Cast<AHMP_AIController>(GetController());
	if (AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", NewTarget);;
	}
}

void AHMP_AICharacter::OnPawnSeen(APawn* Pawn)
{
	SetTargetActor(Pawn);

	DrawDebugString(GetWorld(), GetActorLocation(), "Player SPOTTED", nullptr, FColor::White, 4.0f, true);
}
