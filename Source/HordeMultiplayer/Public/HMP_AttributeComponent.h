// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HMP_AttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, UHMP_AttributeComponent*, OwningComp, float, NewHealth, float, Delta);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORDEMULTIPLAYER_API UHMP_AttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static UHMP_AttributeComponent* GetAttributes(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes", meta = (DisplayName = "IsAlive"))
	static bool IsActorAlive(AActor* Actor);
	
	// Sets default values for this component's properties
	UHMP_AttributeComponent();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float LastDamage;

public:

	UFUNCTION(BlueprintCallable)
	bool Kill(AActor* InstigatorActor);

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool ApplyHealthChange(AActor* InstigatorActor, float Delta);

	UFUNCTION()
	float GetHealth() const;

	UFUNCTION()
	bool IsFullHealth() const;

	UFUNCTION()
	float GetMaxHealth() const;

	UFUNCTION()
	float GetLastDamage() const;

		
};
