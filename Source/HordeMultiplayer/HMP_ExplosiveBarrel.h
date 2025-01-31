// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HMP_ExplosiveBarrel.generated.h"

UCLASS()
class HORDEMULTIPLAYER_API AHMP_ExplosiveBarrel : public AActor
{
	GENERATED_BODY()

protected:

	//UPROPERTY(EditAnywhere)
	//UStaticMeshComponent* BaseMeshComp;

	//UPROPERTY(EditAnywhere)
	//URadialForceComponent* RadialForce;
	
public:	
	// Sets default values for this actor's properties
	AHMP_ExplosiveBarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UFUNCTION(BlueprintCallable)
	//void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
