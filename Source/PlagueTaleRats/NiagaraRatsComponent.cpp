// Fill out your copyright notice in the Description page of Project Settings.


#include "NiagaraRatsComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "PlagueTaleRatsCharacter.h"
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
}

void ANiagaraRatsComponent::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);	
	
	if(CharacterRef && InAttackRange)
	{		
		NiagaraParticleRef->SetVariableVec3(FName("PlayerLocation"), CharacterRef->GetActorLocation());
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

void ANiagaraRatsComponent::BeginPlay()
{
	Super::BeginPlay();
	
	world = GetWorld();
	if(!IsValid(world)) return;
	
	CharacterRef = Cast<APlagueTaleRatsCharacter>(UGameplayStatics::GetActorOfClass(world, APlagueTaleRatsCharacter::StaticClass()));	

	Collider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::BeginOverlap);
	Collider->OnComponentEndOverlap.AddDynamic(this, &ThisClass::EndOverlap);
}




