// Copyright Srujan Lokhande 2024

#include "HealthBarWidget.h"
#include "PlagueTaleRatsCharacter.h"

void UHealthBarWidget::UpdateHealthText()
{
	BAR_HealthBar->SetPercent(CharacterRef->CurrentPlayerHealth / CharacterRef->MaxPlayerHealth);

	FNumberFormattingOptions Opts;
	Opts.SetMaximumFractionalDigits(0);
	TXT_HealthText->SetText(FText::AsNumber(CharacterRef->CurrentPlayerHealth, &Opts));
}

void UHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(!CharacterRef.IsValid())
			return;

	UpdateHealthText();
}
