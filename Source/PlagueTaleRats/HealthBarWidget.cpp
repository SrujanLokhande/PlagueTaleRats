// Copyright Srujan Lokhande 2024

#include "HealthBarWidget.h"
#include "PlagueTaleRatsCharacter.h"

// called whenever the player takes damage
void UHealthBarWidget::UpdateHealthInfo()
{
	if(DamageAnimation)		
		PlayAnimation(DamageAnimation);
	
	BAR_HealthBar->SetPercent(CharacterRef->CurrentPlayerHealth / CharacterRef->MaxPlayerHealth);

	FNumberFormattingOptions Opts;
	Opts.SetMaximumFractionalDigits(0);
	TXT_HealthText->SetText(FText::AsNumber(CharacterRef->CurrentPlayerHealth, &Opts));
}

// sets the default values
void UHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(!CharacterRef)
			return;

	if(BAR_HealthBar == nullptr && TXT_HealthText == nullptr) return;

	BAR_HealthBar->SetPercent(1.0f);
	TXT_HealthText->SetText(FText::AsNumber(100.0f));
}
