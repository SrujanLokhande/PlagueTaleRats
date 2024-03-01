﻿// Copyright Srujan Lokhande 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
class APlagueTaleRatsCharacter;
UCLASS()
class PLAGUETALERATS_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UProgressBar* BAR_HealthBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* TXT_HealthText;

	TWeakObjectPtr<APlagueTaleRatsCharacter> CharacterRef;

	void UpdateHealthText();

	virtual void NativeConstruct() override;

public:
	void SetCharacterOwner(APlagueTaleRatsCharacter* InPlayerCharacter) {CharacterRef = InPlayerCharacter; }
};