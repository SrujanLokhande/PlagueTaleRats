// Copyright Srujan Lokhande 2024


#include "HealthWidgetCpp.h"
#include "PlagueTaleRatsCharacter.h"
#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/SizeBox.h"
#include "Fonts/SlateFontInfo.h"
#include "Fonts/CompositeFont.h"
#include "Styling/SlateStyle.h"
#include "Components/SizeBoxSlot.h"

// called when the widget is constructed on the players screen
void UHealthWidgetCpp::NativeConstruct()
{
	Super::NativeConstruct();
	if(!CharacterRef)
		return;

	if(BAR_HealthBar == nullptr && TXT_HealthText == nullptr) return;

	// initially sets the percentage and text to 100 by default
	BAR_HealthBar->SetPercent(1.0f);
	TXT_HealthText->SetText(FText::AsNumber(100.0f));	
}

// called whenever the players takes damage
void UHealthWidgetCpp::UpdateHealthInfo()
{
	if(DamageAnimation)		
		PlayAnimation(DamageAnimation);
	
	BAR_HealthBar->SetPercent(CharacterRef->CurrentPlayerHealth / CharacterRef->MaxPlayerHealth);

	FNumberFormattingOptions Opts;
	Opts.SetMaximumFractionalDigits(0);
	TXT_HealthText->SetText(FText::AsNumber(CharacterRef->CurrentPlayerHealth, &Opts));
}

// to draw the widget and set the WidgetTree hierarchy 
TSharedRef<SWidget> UHealthWidgetCpp::RebuildWidget()
{
	// sets the Canvas panel as the root of this widget
	UPanelWidget* RootCanvasPanel = Cast<UPanelWidget>(GetRootWidget());
	if(!RootCanvasPanel)
	{		
		RootCanvasPanel = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass(), TEXT("RootWidget"));
		if(UCanvasPanelSlot* RootWidgetSlot = Cast<UCanvasPanelSlot>(RootCanvasPanel->Slot))		
		{
			RootWidgetSlot->SetAnchors(FAnchors(0.0f,0.0f,1.0f,1.0f));
			RootWidgetSlot->SetOffsets(FMargin(0.f,0.f));			
		}
		WidgetTree->RootWidget = RootCanvasPanel;
	}

	if(RootCanvasPanel && WidgetTree)
	{
		// makes horizontal box as child of Canvas Panel
		UHorizontalBox* HorizontalBox = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass(), TEXT("Horizontal Box"));
		RootCanvasPanel->AddChild(HorizontalBox);		
		if(UCanvasPanelSlot* HorizontalBoxSlot = Cast<UCanvasPanelSlot>(HorizontalBox->Slot))
		{
			HorizontalBoxSlot->SetAnchors(FAnchors(0.f, 1.f));
			HorizontalBoxSlot->SetPosition(FVector2D(200.0f, -120.0f));
			HorizontalBoxSlot->SetAutoSize(true);			
		}

		// makes a size box and adds as the child of the horizontal box
		USizeBox* SizeBox = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass(), TEXT("SizeBox"));
		HorizontalBox->AddChildToHorizontalBox(SizeBox);
		
		// the size box slot 
		if(UHorizontalBoxSlot* SizeBoxSlot = Cast<UHorizontalBoxSlot>(SizeBox->Slot))
		{
			SizeBoxSlot->SetHorizontalAlignment(HAlign_Fill);
			SizeBoxSlot->SetVerticalAlignment(VAlign_Fill);
			SizeBox->SetHeightOverride(100.0f);
			SizeBox->SetWidthOverride(150.0f);
		}

		// creates the text slot as the child of the size box
		TXT_HealthText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("TextBox"));
		SizeBox->AddChild(TXT_HealthText);
		if(USizeBoxSlot* TextBoxSlot = Cast<USizeBoxSlot>(TXT_HealthText->Slot))		
		{
			TextBoxSlot->SetHorizontalAlignment(HAlign_Center);
			TextBoxSlot->SetVerticalAlignment(VAlign_Center);					
		}

		// creates the health bar as the child of the Horizontal box
		BAR_HealthBar = WidgetTree->ConstructWidget<UProgressBar>(UProgressBar::StaticClass(), TEXT("ProgressBar"));
		HorizontalBox->AddChildToHorizontalBox(BAR_HealthBar);
		
		if(UHorizontalBoxSlot* HealthBarSlot = Cast<UHorizontalBoxSlot>(BAR_HealthBar->Slot))
		{
			HealthBarSlot->SetHorizontalAlignment(HAlign_Fill);
			HealthBarSlot->SetVerticalAlignment(VAlign_Fill);			
			BAR_HealthBar->SetFillColorAndOpacity(FLinearColor::Red);
			BAR_HealthBar->SetBarFillType(EProgressBarFillType::BottomToTop);
		}		
	}	
	return Super::RebuildWidget();
}






