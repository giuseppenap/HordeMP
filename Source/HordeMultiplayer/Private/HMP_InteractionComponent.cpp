// Fill out your copyright notice in the Description page of Project Settings.



#include "HMP_InteractionComponent.h"
#include "HMP_Gameplay_Interface.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"


static TAutoConsoleVariable<bool> CVarDebutDrawInteraction(TEXT("hmp.InteractionDebuDraw"), false, TEXT("Enable Debug Lines for Interact Component."), ECVF_Cheat);


UHMP_InteractionComponent::UHMP_InteractionComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	TraceDistance = 1000;
	TraceRadius = 30.0f;
	CollisionChannel = ECC_WorldDynamic;
	
}


// Called when the game starts
void UHMP_InteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UHMP_InteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APawn* MyPawn = Cast<APawn>(GetOwner());
	if (MyPawn->IsLocallyControlled())
	{
		FindBestInteractable();
	}

}

void UHMP_InteractionComponent::FindBestInteractable()
{
	bool bDebugDraw = CVarDebutDrawInteraction.GetValueOnGameThread();
 	
 	FCollisionObjectQueryParams ObjectQueryParams;
 	ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);
 
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
 	FVector TraceEnd = TraceStart + (CameraRotation.Vector() * TraceDistance);
 
 	// Perform the trace
	
 	TArray<FHitResult> Hits;
 	FCollisionShape CollisionShape;
 	CollisionShape.SetSphere(TraceRadius);
     
 	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, TraceStart, TraceEnd, FQuat::Identity, ObjectQueryParams, CollisionShape);
 
 	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	// Clear Ref before trying to fill
	FocusedActor = nullptr;
	 
	for (FHitResult Hit: Hits)
	{
		if (bDebugDraw)
		{
			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, TraceRadius, 32, LineColor, false, 2.0f);
		}
		
		TraceEnd = Hit.ImpactPoint;
		AActor* HitActor = Hit.GetActor();
		
		if (HitActor && HitActor->Implements<UHMP_Gameplay_Interface>())
		{
			FocusedActor = HitActor;
			break;
		}
	}

	if (FocusedActor)
	{
		if (DefaultWidgetInstance == nullptr && ensure(DefaultWidgetClass))
		{
			DefaultWidgetInstance = CreateWidget<UHMP_WorldUserWidget>(GetWorld(), DefaultWidgetClass);
		}

		if (DefaultWidgetInstance)
		{
			DefaultWidgetInstance->AttachedActor = FocusedActor;

			if (!DefaultWidgetInstance->IsInViewport())
			{
			DefaultWidgetInstance->AddToViewport();
			}
		}
	}
	else
	{
		if (DefaultWidgetInstance)
		{
			DefaultWidgetInstance->RemoveFromParent();
		}
	}
	
 	// Draw Debug Line
 	if (bDebugDraw)
 	{
 	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, LineColor, false, 2.0f, 0, 2.0f);
 	}
}

void UHMP_InteractionComponent::PrimaryInteract()
{
	ServerInteract(FocusedActor);
}


void UHMP_InteractionComponent::ServerInteract_Implementation(AActor* InFocus)
{
	if (InFocus == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("No focus Actor to Interact"));
		return;
	}

	if (!InFocus->Implements<UHMP_Gameplay_Interface>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Focused Actor does not implement the required interface"));
		return;
	}
	
	APawn* MyPawn = Cast<APawn>(GetOwner());

	if (ensure(InFocus))
	{
	IHMP_Gameplay_Interface::Execute_Interact(InFocus, MyPawn);
	}
	
}


