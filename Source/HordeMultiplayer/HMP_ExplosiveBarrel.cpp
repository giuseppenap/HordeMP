// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_ExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AHMP_ExplosiveBarrel::AHMP_ExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");

}

// Called when the game starts or when spawned
void AHMP_ExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHMP_ExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

