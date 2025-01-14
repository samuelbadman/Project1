// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenMainMenuButtonWidget.h"
#include "Components/TextBlock.h"

UTitleScreenMainMenuButtonWidget::UTitleScreenMainMenuButtonWidget()
{
	ButtonText = FText::FromString(TEXT("DefaultButtonText"));
}

void UTitleScreenMainMenuButtonWidget::OnBecomeActive()
{
	GetTextBlock()->SetColorAndOpacity(ButtonTextActiveColor);
}

void UTitleScreenMainMenuButtonWidget::OnEndActive()
{
	GetTextBlock()->SetColorAndOpacity(ButtonTextInactiveColor);
}

void UTitleScreenMainMenuButtonWidget::Press()
{
	OnPressedDelegate.Broadcast();
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
