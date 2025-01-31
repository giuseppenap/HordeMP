// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_ItemChest.h"


// Sets default values
AHMP_ItemChest::AHMP_ItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110;
}

// Called when the game starts or when spawned
void AHMP_ItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHMP_ItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHMP_ItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}

