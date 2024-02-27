// Copyright Srujan Lokhande 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PLAGUETALERATS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	// Sets default values for this component's properties
	UHealthComponent();

	// updates the health for the actor
	UFUNCTION()
	void UpdateHealth(float InHealth);

	// getter function for CurrentHealth
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetCurrentHealth() const {return CurrentHealth;}

	// getter function for MaxHealth
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMaxHealth() const {return MaxHealth;}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Max Health for the actor
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Health, meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	// Current health for the actor
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Health, meta = (AllowPrivateAccess = "true"))
	float CurrentHealth;

};
