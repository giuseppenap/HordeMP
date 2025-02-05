// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_TargetDummy.h"


// Sets default values
AHMP_TargetDummy::AHMP_TargetDummy()
{
 	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	AttributeComp = CreateDefaultSubobject<UHMP_AttributeComponent>("AttributeComp");
	AttributeComp->OnHealthChanged.AddDynamic(this, &AHMP_TargetDummy::OnHealthChanged);

}




void AHMP_TargetDummy::OnHealthChanged(AActor* InstigatorActor, UHMP_AttributeComponent* OwningComp, float NewHealth,
	float Delta, float MaxHealth)
{
	if (Delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->GetTimeSeconds());
		if (NewHealth == 0.0f)
		{
			MeshComp->SetScalarParameterValueOnMaterials("DissolveAmount", GetWorld()->GetTimeSeconds());
		}
	}
}


void AHMP_TargetDummy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
}