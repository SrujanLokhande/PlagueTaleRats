// Copyright Srujan Lokhande 2024

#pragma once

#include "CoreMinimal.h"
#include "NiagaraActor.h"
#include "NiagaraDataInterfaceExport.h"
#include "NiagaraRatsComponent.generated.h"

/**
 * 
 */

class APlagueTaleRatsCharacter;
class UNiagaraComponent;
class UWorld;
class UBoxComponent;

UCLASS()
class PLAGUETALERATS_API ANiagaraRatsComponent : public ANiagaraActor, public INiagaraParticleCallbackHandler
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
	virtual void ReceiveParticleData_Implementation(const TArray<FBasicParticleData>& Data, UNiagaraSystem* NiagaraSystem, const FVector& SimulationPositionOffset) override;
	
	
protected:
	
	ANiagaraRatsComponent(const FObjectInitializer& ObjectInitializer);

	// On Overlap with the character
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	// Character Reference
	TObjectPtr<APlagueTaleRatsCharacter> CharacterRef;


	// To check if player is in Attack Range
	bool InAttackRange = false;

private:
	
	// character gun damage point reference
	USceneComponent* HitDamagePointRef;	

	// World reference
	TObjectPtr<UWorld> world;

	// Niagara Damage Timer
	int DamageTimer;

	// timer
	FTimerHandle DamageTimerHandle;

	// give damage function
	UFUNCTION()
	void GiveDamage();

	UFUNCTION()
	void DamagePlayer();
};
