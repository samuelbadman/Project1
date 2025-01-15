// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenMainMenuButtonWidget.h"
#include "Components/TextBlock.h"

UTitleScreenMainMenuButtonWidget::UTitleScreenMainMenuButtonWidget()
{
	ButtonText = FText::FromString(TEXT("Default Button Text"));
}

void UTitleScreenMainMenuButtonWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	const TObjectPtr<UTextBlock> TextBlock{ GetTextBlock() };
	if (IsValid(TextBlock))
	{
		TextBlock->SetText(ButtonText);
	}
}

void UTitleScreenMainMenuButtonWidget::NativeOnBecomeActive()
{
	GetTextBlock()->SetColorAndOpacity(ButtonTextActiveColor);
}

void UTitleScreenMainMenuButtonWidget::NativeOnEndActive()
{
	GetTextBlock()->SetColorAndOpacity(ButtonTextInactiveColor);
}
