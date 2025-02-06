// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HMP_AICharacter.h"

#include "AI/HMP_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AHMP_AICharacter::AHMP_AICharacter()
{

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	/*AttributeComp = CreateDefaultSubobject<UHMP_AttributeComponent>("AttributeComp");
	AttributeComp->OnHealthChanged.AddDynamic(this, &AHMP_AICharacter::OnHealthChanged);*/
}

void AHMP_AICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AHMP_AICharacter::OnPawnSeen);
}

void AHMP_AICharacter::OnPawnSeen(APawn* Pawn)
{
	AHMP_AIController* AIC = Cast<AHMP_AIController>(GetController());
	if (AIC)
	{
		UBlackboardComponent* BBComp = AIC->GetBlackboardComponent();

		BBComp->SetValueAsObject("TargetActor", Pawn);

		DrawDebugString(GetWorld(), GetActorLocation(), "Player SPOTTED", nullptr, FColor::White, 4.0f, true);
	}
}

/*void AHMP_AICharacter::OnHealthChanged(AActor* InstigatorActor, UHMP_AttributeComponent* OwningComp, float NewHealth,
	float Delta, float MaxHealth)
{
	if (Delta < 0.0f)
	{
		USkeletalMeshComponent* SKMesh = GetMesh();
		SKMesh->SetScalarParameterValueOnMaterials("HitFlashTime", GetWorld()->GetTimeSeconds());
	}
}*/




