// Copyright Srujan Lokhande 2024

#pragma once

#include "CoreMinimal.h"

#include "PlagueTalePlayerController.generated.h"

UCLASS()
class PLAGUETALERATS_API APlagueTalePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlagueTalePlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
