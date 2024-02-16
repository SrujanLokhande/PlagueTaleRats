// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraActor.h"
#include "NiagaraRatsComponent.generated.h"

/**
 * 
 */

class APlagueTaleRatsCharacter;
class UNiagaraComponent;
class UWorld;
class UBoxComponent;
UCLASS()
class PLAGUETALERATS_API ANiagaraRatsComponent : public ANiagaraActor
{
	GENERATED_BODY()

public:

	// Niagara System asset Reference
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = NiagaraComponent)
	TObjectPtr<UNiagaraComponent> NiagaraParticleRef;

	// Box Collider for collision with the character
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = Collider)
	TObjectPtr<UBoxComponent> Collider;                                             
	
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	
protected:
	
	ANiagaraRatsComponent(const FObjectInitializer& ObjectInitializer);

	// On Overlap with the character
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	// Character Reference
	TObjectPtr<APlagueTaleRatsCharacter> CharacterRef;

	// World reference
	TObjectPtr<UWorld> world;

	// To check if player is in Attack Range
	bool InAttackRange = false;
};
