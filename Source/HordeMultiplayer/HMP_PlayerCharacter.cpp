 // Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_PlayerCharacter.h"

#include "HMP_InteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AHMP_PlayerCharacter::AHMP_PlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UHMP_InteractionComponent>("InteractionComponent");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

}

// Called when the game starts or when spawned
void AHMP_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AHMP_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

 

 // Called to bind functionality to input
void AHMP_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AHMP_PlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHMP_PlayerCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHMP_PlayerCharacter::Jump);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AHMP_PlayerCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AHMP_PlayerCharacter::PrimaryInteract);

}

void AHMP_PlayerCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	
	AddMovementInput(ControlRot.Vector(), Value);
}

void AHMP_PlayerCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	
	AddMovementInput(RightVector, Value);
}

 void AHMP_PlayerCharacter::PrimaryAttack()
 {
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AHMP_PlayerCharacter::PrimaryAttack_TimeElapsed, 0.17f);
 }

void AHMP_PlayerCharacter::PrimaryInteract()
 {
	InteractionComp->PrimaryInteract();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Interact"));
 }

 void AHMP_PlayerCharacter::PrimaryAttack_TimeElapsed()
 {
	SpawnProjectile(ProjectileClass);
	UE_LOG(LogTemp, Warning, TEXT("Player Attack Finished"));
 }

 void AHMP_PlayerCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
 {
	if (ensureAlways(ClassToSpawn))
	{
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		SpawnParams.Instigator = this;

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);

		FVector TraceStart = CameraComp->GetComponentLocation();

		FVector TraceEnd = CameraComp->GetComponentLocation() + (GetControlRotation().Vector() * 5000);

		FHitResult Hit;

		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
		{
			TraceEnd = Hit.ImpactPoint;
		}

		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();

		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);

		//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Cyan, false, 2.0f, 0,2.0f);
	}
 }




