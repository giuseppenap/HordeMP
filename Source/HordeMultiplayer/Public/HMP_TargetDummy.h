// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HMP_AttributeComponent.h"
#include "GameFramework/Actor.h"
#include "HMP_TargetDummy.generated.h"

class UHMP_AttributeComponent;

UCLASS()
class HORDEMULTIPLAYER_API AHMP_TargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHMP_TargetDummy();

protected:

	UPROPERTY(VisibleAnywhere)
	UHMP_AttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UHMP_AttributeComponent* OwningComp, float NewHealth, float Delta, float MaxHealth);


	virtual void PostInitializeComponents() override;
};
