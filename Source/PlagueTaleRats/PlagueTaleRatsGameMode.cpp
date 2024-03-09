// Copyright Srujan Lokhande 2024

#include "PlagueTaleRatsGameMode.h"
#include "PlagueTaleRatsCharacter.h"
#include "UObject/ConstructorHelpers.h"

APlagueTaleRatsGameMode::APlagueTaleRatsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_PlayerController"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}
