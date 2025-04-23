// Fill out your copyright notice in the Description page of Project Settings.


#include "ScrollingTextBlock.h"
#include "Components/TextBlock.h"

UScrollingTextBlock::UScrollingTextBlock()
	:
	TextValue(FText::FromString(TEXT("Scrolling Text Block"))),
	TextColorAndOpacity(FColor::White),
	TextFont(ConstructorHelpers::FObjectFinder<UObject>(*UWidget::GetDefaultFontName()).Object, 24),
	TextJustification(ETextJustify::Left),
	World(nullptr),
	TextBlock(nullptr),
	ScrollTimerHandle(),
	ScrollProgressString(TEXT("")),
	StringCharIndex(0)
{
}

void UScrollingTextBlock::BeginScroll()
{
	ScrollProgressString.Empty();
	StringCharIndex = 0;
	TextBlock->SetText(FText::FromString(ScrollProgressString));

	World->GetTimerManager().SetTimer(ScrollTimerHandle, this, &UScrollingTextBlock::ProgressScroll, ScrollRate, true);
}

void UScrollingTextBlock::StopScroll(bool ShowFullText)
{
	World->GetTimerManager().ClearTimer(ScrollTimerHandle);

	if (ShowFullText)
	{
		TextBlock->SetText(TextValue);
	}
	// TODO: On scroll stopped event here
}

bool UScrollingTextBlock::IsScrolling() const
{
	return World->GetTimerManager().IsTimerActive(ScrollTimerHandle);
}

void UScrollingTextBlock::SetText(const FText& Text)
{
	TextValue = Text;
	TextBlock->SetText(TextValue);
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

	World = GetWorld();
}

void UScrollingTextBlock::ProgressScroll()
{
	const FString& TextValueString{ TextValue.ToString() };

	ScrollProgressString += TextValueString[StringCharIndex++];

	TextBlock->SetText(FText::FromString(ScrollProgressString));

	if (!TextValueString.IsValidIndex(StringCharIndex))
	{
		World->GetTimerManager().ClearTimer(ScrollTimerHandle);
		// TODO: On scroll complete event here
	}
}
