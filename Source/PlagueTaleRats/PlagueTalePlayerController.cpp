// Copyright Srujan Lokhande 2024


#include "PlagueTalePlayerController.h"


// Sets default values
APlagueTalePlayerController::APlagueTalePlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlagueTalePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlagueTalePlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void APlagueTalePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

