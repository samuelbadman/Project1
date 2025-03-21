// Fill out your copyright notice in the Description page of Project Settings.


#include "BinarySettingWidget.h"
#include "Components/TextBlock.h"

UBinarySettingWidget::UBinarySettingWidget()
	: SettingLabel(TEXT("Default Label")),
	SettingValue1Label(TEXT("Default Value 1 Label")),
	SettingValue2Label(TEXT("Default Value 2 Label")),
	OnSettingValueChangedDelegate({}),
	SettingValue(true)
{
}

void UBinarySettingWidget::FlipSettingValue()
{
	SetSettingValue(!SettingValue);
}

void UBinarySettingWidget::SetDefaultSettingValue(bool NewValue)
{
	UpdateSettingValue(NewValue);
}

void UBinarySettingWidget::SetSettingValue(bool NewValue)
{
	UpdateSettingValue(NewValue);
	OnSettingValueChangedDelegate.Broadcast(NewValue);
}

void UBinarySettingWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	// Update setting label text
	if (UTextBlock* SettingLabelTextBlock = GetSettingLabelTextBlock())
	{
		SettingLabelTextBlock->SetText(FText::FromString(SettingLabel + TEXT(":")));
	}

	UpdateSettingValueLabel();
}

ESettingInputResult UBinarySettingWidget::ProcessConfirmInput()
{
	FlipSettingValue();
	return ESettingInputResult::Handled;
}

void UBinarySettingWidget::UpdateSettingValue(bool NewValue)
{
	if (SettingValue == NewValue)
	{
		return;
	}

	SettingValue = NewValue;
	UpdateSettingValueLabel();
}

void UBinarySettingWidget::UpdateSettingValueLabel()
{
	if (UTextBlock* SettingValueLabelTextBlock = GetSettingValueLabelTextBlock())
	{
		SettingValueLabelTextBlock->SetText(FText::FromString(((SettingValue) ? SettingValue1Label : SettingValue2Label)));
	}
}
