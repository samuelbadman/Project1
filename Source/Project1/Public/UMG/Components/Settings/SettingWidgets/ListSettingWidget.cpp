// Fill out your copyright notice in the Description page of Project Settings.


#include "ListSettingWidget.h"
#include "Components/TextBlock.h"
#include "Components/Spacer.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/SizeBox.h"
#include "Components/SizeBoxSlot.h"
#include "FunctionLibraries/Project1MathLibrary.h"

UListSettingWidget::UListSettingWidget()
	: LabelMargin(0.0),
	SettingValueLabelMargin(0.0),
	ValueLabelTextAreaWidth(25.0f),
	SettingValueLabels({}),
	CurrentSettingValueIndex(INDEX_NONE),
	DefaultSettingValueIndex(CurrentSettingValueIndex)
{
}

void UListSettingWidget::SetDefaultSettingValueIndex(int32 Index)
{
	if (SettingValueLabels.IsValidIndex(Index))
	{
		DefaultSettingValueIndex = Index;
		UpdateSettingValue(Index);
	}
}

void UListSettingWidget::SetSettingValueIndex(int32 Index)
{
	if (SettingValueLabels.IsValidIndex(Index))
	{
		UpdateSettingValue(Index);
		OnSettingValueChangedDelegate.Broadcast(Index);
	}
}

void UListSettingWidget::ScrollSettingValue(int32 Increment)
{
	SetSettingValueIndex(UProject1MathLibrary::WrapIncrementArrayIndex(CurrentSettingValueIndex, SettingValueLabels.Num(), Increment));
}

const FText& UListSettingWidget::GetSettingValueLabel(int32 SettingValueIndex) const
{
	return SettingValueLabels[SettingValueIndex];
}

void UListSettingWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	// Update padding of spacer between label and spacer
	if (const TObjectPtr<USpacer> Spacer = GetLabelSpacer())
	{
		CastChecked<UHorizontalBoxSlot>(Spacer->Slot)->SetPadding(LabelMargin);
	}

	// Update padding of value label text
	if (const TObjectPtr<UTextBlock> LabelTextBlock = GetSettingValueLabelTextBlock())
	{
		CastChecked<USizeBoxSlot>(LabelTextBlock->Slot)->SetPadding(SettingValueLabelMargin);
	}

	// Update width override of size box wrapping value label text block widget
	if (const TObjectPtr<USizeBox> LabelSizeBox = GetSettingValueLabelSizeBox())
	{
		LabelSizeBox->SetWidthOverride(ValueLabelTextAreaWidth);
	}
}

ESettingInputResult UListSettingWidget::ProcessNavigationInput(const FVector2D& NavigationInput)
{
	if (NavigationInput.X != 0.0f)
	{
		ScrollSettingValue(StaticCast<int32>(NavigationInput.X));
		return ESettingInputResult::Handled;
	}

	return ESettingInputResult::Unhandled;
}

bool UListSettingWidget::HasSettingValueChanged() const
{
	return (CurrentSettingValueIndex != DefaultSettingValueIndex);
}

void UListSettingWidget::UpdateSettingValue(int32 NewValueIndex)
{
	CurrentSettingValueIndex = NewValueIndex;

	if (UTextBlock* SettingValueLabelTextBlock = GetSettingValueLabelTextBlock())
	{
		SettingValueLabelTextBlock->SetText(SettingValueLabels[NewValueIndex]);
	}
}
