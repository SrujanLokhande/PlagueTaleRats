// Copyright Srujan Lokhande 2024

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidgetCpp.generated.h"

/**
 * 
 */
class UButton;
class APlagueTaleRatsCharacter;
UCLASS()
class PLAGUETALERATS_API UHealthWidgetCpp : public UUserWidget
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

	virtual TSharedRef<SWidget> RebuildWidget() override;	

public:
	void SetCharacterOwner(APlagueTaleRatsCharacter* InPlayerCharacter) {CharacterRef = InPlayerCharacter; }
	void UpdateHealthInfo();
};
