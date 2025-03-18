 // Fill out your copyright notice in the Description page of Project Settings.


#include "HMP_PlayerCharacter.h"

#include "HMP_InteractionComponent.h"
#include "HMP_AttributeComponent.h"
#include "HMP_ActionComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

 // Sets default values
AHMP_PlayerCharacter::AHMP_PlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);
	

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UHMP_InteractionComponent>("InteractionComponent");

	AttributeComp = CreateDefaultSubobject<UHMP_AttributeComponent>("AttributeComponent");

	ActionComp = CreateDefaultSubobject<UHMP_ActionComponent>("ActionComponent");

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

 void AHMP_PlayerCharacter::PostInitializeComponents()
 {
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this, &AHMP_PlayerCharacter::OnHealthChanged);
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

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AHMP_PlayerCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AHMP_PlayerCharacter::SprintStop);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AHMP_PlayerCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AHMP_PlayerCharacter::PrimaryInteract);
	PlayerInputComponent->BindAction("Special", IE_Pressed, this, &AHMP_PlayerCharacter::SpecialAttack);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AHMP_PlayerCharacter::Dash);
	PlayerInputComponent->BindAction("AlternateFire", IE_Pressed, this, &AHMP_PlayerCharacter::AlternateFire);

}

 void AHMP_PlayerCharacter::HealSelf(float Amount /* = 100 */)
 {
	AttributeComp->ApplyHealthChange(this, Amount);
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

 void AHMP_PlayerCharacter::SprintStart()
 {
	ActionComp->StartActionByName(this, "Sprint");
 }

 void AHMP_PlayerCharacter::SprintStop()
 {
	ActionComp->StopActionByName(this, "Sprint");
 }

 void AHMP_PlayerCharacter::PrimaryAttack()
 {
	ActionComp->StartActionByName(this, "PrimaryAttack");
 }

void AHMP_PlayerCharacter::SpecialAttack()
 {
	ActionComp->StartActionByName(this, "SpecialAttack");
 }

 void AHMP_PlayerCharacter::Dash()
 {
	ActionComp->StartActionByName(this, "Dash");
 }

 void AHMP_PlayerCharacter::AlternateFire()
 {
	ActionComp->StartActionByName(this, "AlternateFire");
 }

 void AHMP_PlayerCharacter::PrimaryInteract()
 {
	InteractionComp->PrimaryInteract();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Interact"));
 }

 void AHMP_PlayerCharacter::OnHealthChanged(AActor* InstigatorActor, UHMP_AttributeComponent* OwningComp,
	 float NewHealth, float Delta)
 {
	if (Delta > 0.0f)
	{
		//GetMesh()->SetVectorParameterValueOnMaterials(HealColor, )
	}
	if (Delta < 0.0f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->GetTimeSeconds());
		APlayerController* PC = Cast<APlayerController>(GetController());
		AttributeComp->ApplyRageChange(InstigatorActor, FMath::Abs(Delta));
		if (PC)
		{
			PC->ClientStartCameraShake(ImpactCameraShake);
		}
	}

	// Died
	if (NewHealth <= 0.0f && Delta < 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		if (PC)
		{
			PC->ClientStartCameraShake(DeathCameraShake);
			DisableInput(PC);
		}
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		SetLifeSpan(5.0f);
	}
 }

 FVector AHMP_PlayerCharacter::GetPawnViewLocation() const
 {
	 return CameraComp->GetComponentLocation();
 }




