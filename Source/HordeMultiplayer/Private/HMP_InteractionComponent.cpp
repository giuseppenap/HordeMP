// Fill out your copyright notice in the Description page of Project Settings.



#include "HMP_InteractionComponent.h"
#include "HMP_Gameplay_Interface.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"




// Sets default values for this component's properties
UHMP_InteractionComponent::UHMP_InteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHMP_InteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHMP_InteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHMP_InteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();
	if (!MyOwner)
	{
		return;
	}

	// Get Camera Component
	UCameraComponent* CameraComp = MyOwner->FindComponentByClass<UCameraComponent>();
	if (!CameraComp)
	{
		return;
	}

	FVector CameraLocation = CameraComp->GetComponentLocation();
	FRotator CameraRotation = CameraComp->GetComponentRotation(); // Get Rotation

	// Line trace forward from the camera
	FVector TraceStart = CameraLocation;
	FVector TraceEnd = TraceStart + (CameraRotation.Vector() * 5000);

	// Perform the trace
	FHitResult Hit;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(30.0f);
    
	bool bBlockingHit = GetWorld()->SweepSingleByObjectType(
		Hit, TraceStart, TraceEnd, FQuat::Identity, ObjectQueryParams, CollisionShape
	);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	if (bBlockingHit)
	{
		TraceEnd = Hit.ImpactPoint;
		AActor* HitActor = Hit.GetActor();
		if (HitActor && HitActor->Implements<UHMP_Gameplay_Interface>())
		{
			APawn* MyPawn = Cast<APawn>(MyOwner);
			IHMP_Gameplay_Interface::Execute_Interact(HitActor, MyPawn);
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 30.0f, 32, LineColor, false, 2.0f);
		}
	}

	// Draw Debug Line
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, LineColor, false, 2.0f, 0, 2.0f);
}