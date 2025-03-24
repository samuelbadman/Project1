// Fill out your copyright notice in the Description page of Project Settings.


#include "ListSettingWidget.h"
#include "Components/TextBlock.h"
#include "FunctionLibraries/Project1MathLibrary.h"

UListSettingWidget::UListSettingWidget()
	: SettingValueLabels({}),
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
