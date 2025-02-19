// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HMP_Action.h"
#include "Components/ActorComponent.h"
#include "HMP_ActionComponent.generated.h"

class UHMP_Action;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORDEMULTIPLAYER_API UHMP_ActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Action")
	void AddAction(TSubclassOf<UHMP_Action> ActionClass);

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool StartActionByName(AActor* Instigator, FName ActionName);
	
	UFUNCTION(BlueprintCallable, Category = "Action")
	bool StopActionByName(AActor* Instigator, FName ActionName);


	

	UHMP_ActionComponent();

protected:

	/* Grants abilities at game start */
	UPROPERTY(EditAnywhere, Category = "Action")
	TArray<TSubclassOf<UHMP_Action>> DefaultActions;
	
	UPROPERTY()
	TArray<UHMP_Action*> Actions;

	
	virtual void BeginPlay() override;

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
