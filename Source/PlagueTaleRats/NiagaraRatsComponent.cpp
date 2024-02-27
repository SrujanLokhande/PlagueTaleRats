// Fill out your copyright notice in the Description page of Project Settings.


#include "NiagaraRatsComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "PlagueTaleRatsCharacter.h"
#include "Utils.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Microsoft/AllowMicrosoftPlatformTypes.h"
#include "UObject/ConstructorHelpers.h"

ANiagaraRatsComponent::ANiagaraRatsComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	NiagaraParticleRef = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraRats"));
	NiagaraParticleRef->SetupAttachment(RootComponent);
	
	// assigns the Niagara system to the component
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystemAssetRef(TEXT("/Script/Niagara.NiagaraSystem'/Game/Niagara/NS_PlagueRats.NS_PlagueRats'"));
	if(NiagaraSystemAssetRef.Succeeded())
	{		
		NiagaraParticleRef->SetAsset(NiagaraSystemAssetRef.Object);
	}
 
	Collider = CreateDefaultSubobject<UBoxComponent>("Collider");
	Collider->SetupAttachment(RootComponent);
	Collider->SetWorldScale3D(FVector3d(30.0f, 30.0f, 1.0f));

	DamageTimer = 50;	
}

void ANiagaraRatsComponent::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(IsValid(CharacterRef->HitDamagePoint))
	{		
		NiagaraParticleRef->SetNiagaraVariableVec3(FString("BulletPoint"), CharacterRef->HitDamagePoint->GetComponentLocation());	
		
		if(CharacterRef)
		{			
			NiagaraParticleRef->SetVariableVec3(FName("PlayerLocation"), CharacterRef->GetActorLocation());
			DamageTimer++;

			// if the damage timer is less than 20 than give damage to player
			if(DamageTimer < 20)			
			{
				DamageTimer += DamageTimer;
				if(!DamageTimerHandle.IsValid())
				{
					world->GetTimerManager().SetTimer(DamageTimerHandle, this, &ANiagaraRatsComponent::GiveDamage, 1.0f, true);					
				}				
			}
			else
			{				
				DamageTimer = 20.0f;				
				world->GetTimerManager().ClearTimer(DamageTimerHandle);
			}
		}
	}
	
}

void ANiagaraRatsComponent::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	InAttackRange = true;
	NiagaraParticleRef->SetVariableFloat(FName("AttackRange"), 1.0f);	
}

void ANiagaraRatsComponent::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InAttackRange = false;
	NiagaraParticleRef->SetVariableFloat(FName("AttackRange"), 0);	
}

void ANiagaraRatsComponent::GiveDamage()
{
	CharacterRef->CustomTakeDamage();
	//UGameplayStatics::ApplyDamage(CharacterRef, 10.0f, GetInstigatorController(), this, UDamageType::StaticClass());	
	// CharacterRef->CurrentHealthCpp = CharacterRef->CurrentHealthCpp - 10;		
}

void ANiagaraRatsComponent::BeginPlay()
{
	Super::BeginPlay();
	
	world = GetWorld();
	if(!IsValid(world)) return;

	NiagaraParticleRef->SetNiagaraVariableObject(FString("CB_Interact"), this);
	
	CharacterRef = Cast<APlagueTaleRatsCharacter>(UGameplayStatics::GetActorOfClass(world, APlagueTaleRatsCharacter::StaticClass()));
	
	// if(CharacterRef->HitDamagePoint)
	// {
	// 	HitDamagePointRef = CharacterRef->HitDamagePoint;
	// }

	Collider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::BeginOverlap);
	Collider->OnComponentEndOverlap.AddDynamic(this, &ThisClass::EndOverlap);	
}

void ANiagaraRatsComponent::ReceiveParticleData_Implementation(const TArray<FBasicParticleData>& Data,
	UNiagaraSystem* NiagaraSystem, const FVector& SimulationPositionOffset)
{
	INiagaraParticleCallbackHandler::ReceiveParticleData_Implementation(Data, NiagaraSystem, SimulationPositionOffset);
	for (FBasicParticleData ParticleData : Data)
	{
		// if the rats are near to player than activate the timer
		if(ParticleData.Size != 5)
		{			
			DamageTimer = 0;			
		}
		else
		{			
			LOG(-20, "Spawn Decal here");
		}
	}
}






