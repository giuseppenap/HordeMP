// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UI/HMP_WorldUserWidget.h"
#include "HMP_InteractionComponent.generated.h"

class UHMP_WorldUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORDEMULTIPLAYER_API UHMP_InteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	void PrimaryInteract();

protected:

	// Reliable - Will always arrive, eventually. Request will be re-sent unless an acknowledgment was received.
	// Unreliable - Not guaranteed, packet can get lost and won't retry.

	UFUNCTION(Server, Reliable)
	void ServerInteract(AActor* InFocus);
	
	virtual void BeginPlay() override;
	
	void FindBestInteractable();

	UPROPERTY(EditDefaultsOnly, Category = Config)
	float TraceDistance;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	float TraceRadius;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UPROPERTY()
	AActor* FocusedActor;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UHMP_WorldUserWidget> DefaultWidgetClass;

	UPROPERTY()
	UHMP_WorldUserWidget* DefaultWidgetInstance;
	

public:	
	// Sets default values for this component's properties
	UHMP_InteractionComponent();


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
