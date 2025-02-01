// Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_ExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AHMP_ExplosiveBarrel::AHMP_ExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMeshComp->SetSimulatePhysics(true);
	RootComponent = BaseMeshComp;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForce->SetupAttachment(BaseMeshComp);

	RadialForce->SetAutoActivate(false);

	RadialForce->Radius = 750.0f;
	RadialForce->ImpulseStrength = 2500.0f;
	RadialForce->bImpulseVelChange = false;
	RadialForce->AddCollisionChannelToAffect(ECC_WorldDynamic);

}

void AHMP_ExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	BaseMeshComp->OnComponentHit.AddDynamic(this, &AHMP_ExplosiveBarrel::OnActorHit);
}

void AHMP_ExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForce->FireImpulse();

	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	FString CombinedString = FString::Printf(TEXT("Hit at Location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);
}

// Called when the game starts or when spawned
void AHMP_ExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
		
}

// Called every frame
void AHMP_ExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}





