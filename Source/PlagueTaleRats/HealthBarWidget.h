// Copyright Srujan Lokhande 2024

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

	TObjectPtr<APlagueTaleRatsCharacter> CharacterRef;

	virtual void NativeConstruct() override;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* DamageAnimation;	

public:
	void SetCharacterOwner(APlagueTaleRatsCharacter* InPlayerCharacter) {CharacterRef = InPlayerCharacter; }
	void UpdateHealthInfo();
};
