// Copyright Srujan Lokhande 2024

#include "PlagueTaleRatsCharacter.h"

#include <string.h>
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HealthComponent.h"
#include "InputActionValue.h"
#include "Utils.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);


APlagueTaleRatsCharacter::APlagueTaleRatsCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Gun Mesh
	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Gun Mesh");
	GunMesh->CastShadow = false;
	GunMesh->SetOnlyOwnerSee(true);
	GunMesh->SetupAttachment(this->GetMesh(), this->WeaponSocket);	

	// MuzzleLocation
	ShootPoint = CreateDefaultSubobject<USceneComponent>("Muzzle Location");
	ShootPoint->SetupAttachment(GunMesh);

	// DamageLocation for niagara particle
	HitDamagePoint = CreateDefaultSubobject<USceneComponent>("Damage Point");
	HitDamagePoint->SetupAttachment(GunMesh);
	HitDamagePoint->SetWorldLocation(FVector3d(30.0f, 10.0f, 0.0f));

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Health Component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Characters Health Component");

	// Character default health
	MaxPlayerHealth = HealthComponent->GetMaxHealth();
	CurrentPlayerHealth = MaxPlayerHealth;
	IsShooting = false;
	DistanceFromCamera = 500.0f;
}

void APlagueTaleRatsCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}	
}

void APlagueTaleRatsCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FString FloatAsString = FString::Printf(TEXT("%f"), HealthComponent->GetCurrentHealth());
	LOG(-1, FloatAsString);	
	
	if(IsShooting)
	{		
		CameraLocation = FollowCamera->GetComponentLocation();
		CameraRotation = FollowCamera->GetComponentRotation();

		// gets the camera forward vector and adds it to the location to make the damage point damage the niagara 
		CameraLocation = CameraLocation + CameraRotation.Vector() * DistanceFromCamera;
		HitDamagePoint->SetWorldLocation(CameraLocation, false);			
	}
}

float APlagueTaleRatsCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,	AController* EventInstigator, AActor* DamageCauser)
{
	const float returnValue =  Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if(!IsValid(HealthComponent))
	{
		return returnValue;
	}
	
	HealthComponent->UpdateHealth(DamageAmount);
	CurrentPlayerHealth = HealthComponent->GetCurrentHealth();
	
	return returnValue;
	
}
void APlagueTaleRatsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlagueTaleRatsCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlagueTaleRatsCharacter::Look);

		// Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &ThisClass::Shoot);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &ThisClass::StopShoot);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APlagueTaleRatsCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlagueTaleRatsCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlagueTaleRatsCharacter::Shoot()
{	
	IsShooting = true;
}

void APlagueTaleRatsCharacter::StopShoot()
{
	IsShooting = false;	
}
