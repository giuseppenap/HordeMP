// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "HMP_Gameplay_Interface.h"
#include "Components/SphereComponent.h"
#include "HMP_PickupBase.generated.h"

UCLASS()
class HORDEMULTIPLAYER_API AHMP_PickupBase : public AActor, public IHMP_Gameplay_Interface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHMP_PickupBase();

	void Interact_Implementation(APawn* InstigatorPawn);


protected:

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	UNiagaraComponent* MeshVFX;

	/*UPROPERTY(EditDefaultsOnly, Category = "Config")
	USphereComponent* SphereCollision;*/
	
	

	
public:

	

};
