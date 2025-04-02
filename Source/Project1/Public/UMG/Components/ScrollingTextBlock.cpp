// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrollingTextBlock.h"
#include "Components/TextBlock.h"

UScrollingTextBlock::UScrollingTextBlock()
	:
	TextValue(FText::FromString(TEXT("Scrolling Text Block"))),
	TextColorAndOpacity(FColor::White),
	TextFont(ConstructorHelpers::FObjectFinder<UObject>(*UWidget::GetDefaultFontName()).Object, 24),
	TextJustification(ETextJustify::Left),
	TextBlock(nullptr)
{
}

void UScrollingTextBlock::NativePreConstruct()
{
	Super::NativePreConstruct();

	TextBlock = GetTextBlock();

	if (IsValid(TextBlock))
	{
		TextBlock->SetText(TextValue);
		TextBlock->SetColorAndOpacity(TextColorAndOpacity);
		TextBlock->SetFont(TextFont);
		TextBlock->SetJustification(TextJustification);
	}
}

void UScrollingTextBlock::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}
