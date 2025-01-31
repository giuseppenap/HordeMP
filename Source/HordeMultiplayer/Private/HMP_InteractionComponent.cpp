// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_InteractionComponent.h"

#include "ContentBrowserItemData.h"
#include "HMP_Gameplay_Interface.h"
#include "DrawDebugHelpers.h"
#include "InputBehavior.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "Evaluation/IMovieSceneEvaluationHook.h"


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

	FVector Eyelocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(Eyelocation, EyeRotation);

	FVector End = Eyelocation + (EyeRotation.Vector() * 1000);
	
	//FHitResult Hit;
	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, Eyelocation, End, ObjectQueryParams);
	TArray<FHitResult> Hits;

	float Radius = 30.0f;
	
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(Radius);
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, Eyelocation, End, FQuat::Identity, ObjectQueryParams, CollisionShape);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UHMP_Gameplay_Interface>())
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Hitactor is: ")) + HitActor->GetName());
				APawn* MyPawn = Cast<APawn>(MyOwner);
			
				IHMP_Gameplay_Interface::Execute_Interact(HitActor, MyPawn);
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "HitActor was nullptr");
		}
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2.0f);
	}
	

	DrawDebugLine(GetWorld(), Eyelocation, End, LineColor, false, 2.0f, 0,2.0f);
}