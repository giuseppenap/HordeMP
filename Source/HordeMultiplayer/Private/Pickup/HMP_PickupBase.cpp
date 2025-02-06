// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup/HMP_PickupBase.h"

#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"

class UStaticMeshComponent;

// Sets default values
AHMP_PickupBase::AHMP_PickupBase()
{

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	MeshVFX = CreateDefaultSubobject<UNiagaraComponent>("MeshVFX");
	MeshVFX->SetupAttachment(RootComponent);

	/*SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollision->SetupAttachment(RootComponent);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	SphereCollision->SetCollisionProfileName("Pickup");*/
	
 

}

void AHMP_PickupBase::Interact_Implementation(APawn* InstigatorPawn)
{
	IHMP_Gameplay_Interface::Interact_Implementation(InstigatorPawn);
}



