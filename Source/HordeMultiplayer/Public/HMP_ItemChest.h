// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HMP_Gameplay_Interface.h"
#include "GameFramework/Actor.h"
#include "HMP_ItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class HORDEMULTIPLAYER_API AHMP_ItemChest : public AActor, public IHMP_Gameplay_Interface
{
	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere)
	float TargetPitch;
	
	void Interact_Implementation(APawn* InstigatorPawn);
	
public:	
	// Sets default values for this actor's properties
	AHMP_ItemChest();

protected:

	UPROPERTY(ReplicatedUsing="OnRep_LidOpened", BlueprintReadOnly) // RepNotify
	bool bLidOpened;

	UFUNCTION()
	void OnRep_LidOpened();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* LidMesh;

	
};
