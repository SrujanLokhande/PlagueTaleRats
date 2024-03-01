﻿// Copyright Srujan Lokhande 2024

#include "HealthBarWidget.h"
#include "PlagueTaleRatsCharacter.h"

void UHealthBarWidget::UpdateHealthInfo()
{
	BAR_HealthBar->SetPercent(CharacterRef->CurrentPlayerHealth / CharacterRef->MaxPlayerHealth);

	FNumberFormattingOptions Opts;
	Opts.SetMaximumFractionalDigits(0);
	TXT_HealthText->SetText(FText::AsNumber(CharacterRef->CurrentPlayerHealth, &Opts));
}

void UHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(!CharacterRef)
			return;

	if(BAR_HealthBar == nullptr && TXT_HealthText == nullptr) return;

	BAR_HealthBar->SetPercent(1.0f);
	TXT_HealthText->SetText(FText::AsNumber(100.0f));
}
