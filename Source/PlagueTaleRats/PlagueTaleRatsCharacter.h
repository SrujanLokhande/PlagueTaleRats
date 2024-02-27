// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "PlagueTaleRatsCharacter.generated.h"

class USceneComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class APlagueTaleRatsCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	// Shoot Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Shooting, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	// Is Player currently shooting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shoot, meta = (AllowPrivateAccess = "true"))
	bool IsShooting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shoot, meta = (AllowPrivateAccess = "true"))
	float DistanceFromCamera;
	
	FVector CameraLocation;
	FRotator CameraRotation;
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	APlagueTaleRatsCharacter();
	
	// Gun Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	USkeletalMeshComponent* GunMesh;

	// Shoot Point
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	USceneComponent* ShootPoint;

	// Niagara Damage Point
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	USceneComponent* HitDamagePoint;

	// Weapon Socket for Weapon attachment
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Gun)
	FName WeaponSocket;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health, meta = (AllowPrivateAccess = "true"))
	float CurrentHealthCpp;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION()
	void CustomTakeDamage();
	
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
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds);

};

