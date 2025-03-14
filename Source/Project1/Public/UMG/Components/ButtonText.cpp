// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonText.h"
#include "Components/TextBlock.h"

UButtonText::UButtonText()
	: ButtonTextValue(FText::FromString(TEXT("Text Block")))
{
}

void UButtonText::SetTextValue(const FText& Text)
{
	ButtonTextValue = Text;
	GetTextBlock()->SetText(Text);
}

void UButtonText::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (UTextBlock* TextBlock = GetTextBlock())
	{
		TextBlock->SetText(ButtonTextValue);
	}
}
