// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/HMP_AICharacter.h"

// Sets default values
AHMP_AICharacter::AHMP_AICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHMP_AICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHMP_AICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


