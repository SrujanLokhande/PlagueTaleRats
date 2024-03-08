// Copyright Srujan Lokhande 2024


#include "PlagueTalePlayerController.h"
#include "PlagueTaleRatsCharacter.h"
#include "HealthBarWidget.h"
#include "HealthWidgetCpp.h"
#include "Utils.h"
#include "Blueprint/UserWidget.h"


// Sets default values
APlagueTalePlayerController::APlagueTalePlayerController()
{	
}

void APlagueTalePlayerController::UpdateWidgetInfo()
{
	// HealthBarWidget->UpdateHealthInfo();
	HealthWidgetCpp->UpdateHealthInfo();
}

// Called when the game starts or when spawned
void APlagueTalePlayerController::BeginPlay()
{
	Super::BeginPlay();

	APlagueTaleRatsCharacter* CharacterRef = GetPawn<APlagueTaleRatsCharacter>();
	if(CharacterRef == nullptr) return;
	//
	// if(WidgetBlueprint == nullptr) return;
	//
	//  UHealthBarWidget* WidgetRef = CreateWidget<UHealthBarWidget>(this, WidgetBlueprint);	
	//
	//  HealthBarWidget = Cast<UHealthBarWidget>(WidgetRef);
	//  if(HealthBarWidget)
	//  {
	//  	HealthBarWidget->SetCharacterOwner(CharacterRef);
	//  	if(!HealthBarWidget->IsInViewport())
	//  	{
	//  		HealthBarWidget->AddToViewport();			
	//  	}
	//  }

	HealthWidgetCpp = CreateWidget<UHealthWidgetCpp>(GetWorld(), UHealthWidgetCpp::StaticClass());
	if(HealthWidgetCpp == nullptr) return;

	HealthWidgetCpp->SetCharacterOwner(CharacterRef);
	HealthWidgetCpp->AddToViewport(100);	
	
}

void APlagueTalePlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	// HealthBarWidget->RemoveFromParent();
	// HealthBarWidget = nullptr;
}


