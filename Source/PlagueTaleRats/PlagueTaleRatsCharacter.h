// Copyright Srujan Lokhande 2024

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "PlagueTaleRatsCharacter.generated.h"

class ULegacyCameraShake;
class APlagueTalePlayerController;
class USceneComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UHealthComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class APlagueTaleRatsCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	// Shoot Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Shooting, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ShootAction;

	// Is Player currently shooting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shoot, meta = (AllowPrivateAccess = "true"))
	bool IsShooting;

	// HitPoint distance from the camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shoot, meta = (AllowPrivateAccess = "true"))
	float DistanceFromCamera;

	// Health Component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Shooting, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY()
	TObjectPtr<APlagueTalePlayerController> PlayerControllerRef;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> CameraShake;
	
	FVector CameraLocation;
	FRotator CameraRotation;
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	APlagueTaleRatsCharacter();
	
	// Gun Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	TObjectPtr<USkeletalMeshComponent> GunMesh;

	// Shoot Point
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	TObjectPtr<USceneComponent> ShootPoint;

	// Niagara Damage Point
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	TObjectPtr<USceneComponent> HitDamagePoint;

	// Weapon Socket for Weapon attachment
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Gun)
	FName WeaponSocket;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health, meta = (AllowPrivateAccess = "true"))
	float CurrentPlayerHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health, meta = (AllowPrivateAccess = "true"))
	float MaxPlayerHealth;

	/** Returns CameraBoom SubObject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	/** Returns FollowCamera SubObject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// returns if the player is shooting or not
	FORCEINLINE bool GetIsShooting() const {return IsShooting;}
	
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// Called for shooting
	void Shoot();

	void StopShoot();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

};

