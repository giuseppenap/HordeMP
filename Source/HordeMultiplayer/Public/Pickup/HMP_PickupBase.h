// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HMP_Gameplay_Interface.h"
#include "Components/SphereComponent.h"
#include "HMP_PickupBase.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class HORDEMULTIPLAYER_API AHMP_PickupBase : public AActor, public IHMP_Gameplay_Interface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHMP_PickupBase();

	void Interact_Implementation(APawn* InstigatorPawn);


protected:

	UPROPERTY(ReplicatedUsing="OnRep_IsActive")
	bool bIsActive;

	UFUNCTION()
	void OnRep_IsActive();

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	USphereComponent* SphereCollision;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	UStaticMeshComponent* MeshComp;

	FTimerHandle TimerHandle_RespawnTimer;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	float RespawnTime;

	UFUNCTION()
	void ShowPowerup();
	
	void SetPowerupState(bool bNewIsActive);
	
	void HideAndCooldownPowerup();
	

};
