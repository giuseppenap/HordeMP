// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HMP_AICharacter.h"

#include "BrainComponent.h"
#include "HMP_ActionComponent.h"
#include "AI/HMP_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HMP_AttributeComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/PawnSensingComponent.h"
#include "UI/HMP_WorldUserWidget.h"


// Sets default values
AHMP_AICharacter::AHMP_AICharacter()
{

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AttributeComp = CreateDefaultSubobject<UHMP_AttributeComponent>("AttributeComp");

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);

	TimeToHitParameter = "HitFlashTime";

	ActionComp = CreateDefaultSubobject<UHMP_ActionComponent>("ActionComp");
	
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
		}


		if (ActiveHealthBar == nullptr)
		{
			ActiveHealthBar = CreateWidget<UHMP_WorldUserWidget>(GetWorld(), HealthBarWidgetClass);
			if (ActiveHealthBar)
			{
				ActiveHealthBar->AttachedActor = this;
				ActiveHealthBar->AddToViewport();
			}
		}
		
		
		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParameter, GetWorld()->GetTimeSeconds());

		if (NewHealth <= 0.0f)
		{
			// stop BT
			AAIController* AIC = Cast<AAIController>(GetController());
			if (AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Killed");
			}

			UGameplayStatics::PlaySoundAtLocation(this, DeathSoundClass, GetActorLocation(), GetActorRotation(), 1.0f, 1.0f, 0.0f, AttenuationDeath);
			// ragdoll
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();

			// set lifespan
			SetLifeSpan(10.0f);
		}

	}
}



void AHMP_AICharacter::SetTargetActor(AActor* NewTarget)
{
	AAIController* AIC = Cast<AHMP_AIController>(GetController());
	if (AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject( "TargetActor", NewTarget);;
	}
}


void AHMP_AICharacter::OnPawnSeen(APawn* Pawn)
{

	// Ignore if target already set
	if (GetTargetActor() != Pawn)
	{
		SetTargetActor(Pawn);

		MulticastPawnSeen();
	}

	//DrawDebugString(GetWorld(), GetActorLocation(), "Player SPOTTED", nullptr, FColor::White, 4.0f, true);
}

AActor* AHMP_AICharacter::GetTargetActor() const
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		return Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject("TargetActor"));
	}

	return nullptr;
}


void AHMP_AICharacter::MulticastPawnSeen_Implementation()
{
	if (SpottedWidgetClass)
	{
		UHMP_WorldUserWidget* NewWidget = CreateWidget<UHMP_WorldUserWidget>(GetWorld(), SpottedWidgetClass);
	    if (NewWidget)
	    {
    		NewWidget->AttachedActor = this;
    		// Index of 10 (or anything higher than default of 0) places this on top of any other widget.
    		// May end up behind the minion health bar otherwise.
    		NewWidget->AddToViewport(10);
	    }
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Seen Widget was not assigned in Enemy Blueprint! Please Assign it!, Instigator : %s"), *GetName());
	}
}