// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_AttributeComponent.h"

#include "HMP_GameModeBase.h"
#include "Net/UnrealNetwork.h"


static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("hmp.DamageMultiplier"), 1.0f, TEXT("Global Damage Modifier for Attribute Component."), ECVF_Cheat);

// Sets default values for this component's properties
UHMP_AttributeComponent::UHMP_AttributeComponent()
{
	Health = 100;
	MaxHealth = 100;

	SetIsReplicatedByDefault(true);
}




bool UHMP_AttributeComponent::Kill(AActor* InstigatorActor)
{
	const auto bIsResult =  ApplyHealthChange(InstigatorActor, -MaxHealth);
	ensure(IsAlive());
	return bIsResult;
}

bool UHMP_AttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

float UHMP_AttributeComponent::GetHealth() const
{
	return Health;
}

bool UHMP_AttributeComponent::IsFullHealth() const
{
	return Health == MaxHealth;
}

float UHMP_AttributeComponent::GetMaxHealth() const
{
	return MaxHealth;
}

float UHMP_AttributeComponent::GetLastDamage() const
{
	return LastDamage;
}

float UHMP_AttributeComponent::GetRage() const
{
	return Rage;
}

float UHMP_AttributeComponent::GetMaxRage() const
{
	return MaxRage;
}

bool UHMP_AttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged() && Delta < 0.0f)
	{
		return false;
	}

	if (Delta < 0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();

		Delta *= DamageMultiplier;
	}
	
	float OldHealth = Health;
	float NewHealth =FMath::Clamp(Health + Delta, 0.0f, MaxHealth); 
	float ActualDelta = NewHealth - OldHealth;
	LastDamage = ActualDelta;
	
	// Is Server?
	if (GetOwner()->HasAuthority())
	{
		Health = NewHealth;
		if (ActualDelta != 0.0f)
		{
			MulticastHealthChanged(InstigatorActor, Health, ActualDelta);
		}
		// Died
		if (ActualDelta < 0.0f && Health == 0.0f)
		{
			AHMP_GameModeBase* GM = GetWorld()->GetAuthGameMode<AHMP_GameModeBase>();
			if (GM)
			{
				GM->OnActorKilled(GetOwner(), InstigatorActor); 
			}
		}
	}
	
	return ActualDelta != 0;
}

bool UHMP_AttributeComponent::ApplyRageChange(AActor* InstigatorActor, float Delta)
{


	float OldRage = Rage;

	Rage = FMath::Clamp(Rage + Delta, 0.0f, MaxRage);

	float ActualDelta = Rage - OldRage;

	if (GetOwner()->HasAuthority())
	{
		if (ActualDelta != 0.0f)
		{
			MulticastRageChanged(InstigatorActor, Rage, ActualDelta);
		}
	}
	
	UE_LOG(LogTemp, Log, TEXT("%f"), Rage);

	return ActualDelta != 0;
}


UHMP_AttributeComponent* UHMP_AttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<UHMP_AttributeComponent>(FromActor->GetComponentByClass(UHMP_AttributeComponent::StaticClass()));
	}

	return nullptr;
}

bool UHMP_AttributeComponent::IsActorAlive(AActor* Actor)
{
	UHMP_AttributeComponent* AttributeComp = GetAttributes(Actor);
	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}
	
	return false;
}

void UHMP_AttributeComponent::MulticastHealthChanged_Implementation(AActor* InstigatorActor, float NewHealth,
	float Delta)
{
	OnHealthChanged.Broadcast(InstigatorActor, this, NewHealth, Delta);
}

void UHMP_AttributeComponent::MulticastRageChanged_Implementation(AActor* InstigatorActor, float NewRage, float Delta)
{
	OnRageChanged.Broadcast(InstigatorActor, this, NewRage, Delta); 
}

void UHMP_AttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHMP_AttributeComponent, Health);
	DOREPLIFETIME(UHMP_AttributeComponent, MaxHealth);
	DOREPLIFETIME(UHMP_AttributeComponent, Rage);
	DOREPLIFETIME(UHMP_AttributeComponent, MaxRage);

	//DOREPLIFETIME_CONDITION(UHMP_AttributeComponent, MaxHealth, COND_OwnerOnly);
}



