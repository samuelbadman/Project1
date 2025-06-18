// Fill out your copyright notice in the Description page of Project Settings.


#include "BinarySettingWidget.h"
#include "Components/TextBlock.h"
#include "Components/Spacer.h"
#include "Components/HorizontalBoxSlot.h"

UBinarySettingWidget::UBinarySettingWidget()
	: LabelMargin(0.0),
	SettingValue1Label(TEXT("Default Value 1 Label")),
	SettingValue2Label(TEXT("Default Value 2 Label")),
	OnSettingValueChangedDelegate({}),
	SettingValue(true),
	DefaultSettingValue(SettingValue)
{
}

void UBinarySettingWidget::FlipSettingValue()
{
	SetSettingValue(!SettingValue);
}

void UBinarySettingWidget::SetDefaultSettingValue(bool NewValue)
{
	DefaultSettingValue = NewValue;
	UpdateSettingValue(NewValue);
}

void UBinarySettingWidget::SetSettingValue(bool NewValue)
{
	UpdateSettingValue(NewValue);
	OnSettingValueChangedDelegate.Broadcast(((NewValue) ? EBinarySettingValue::Value1 : EBinarySettingValue::Value2));
}

void UBinarySettingWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	// Update padding of spacer between label and spacer
	if (const TObjectPtr<USpacer> Spacer = GetLabelSpacer())
	{
		CastChecked<UHorizontalBoxSlot>(Spacer->Slot)->SetPadding(LabelMargin);
	}

	UpdateSettingValueLabel();
}

ESettingInputResult UBinarySettingWidget::ProcessConfirmInput()
{
	FlipSettingValue();
	return ESettingInputResult::Handled;
}

bool UBinarySettingWidget::HasSettingValueChanged() const
{
	return (SettingValue != DefaultSettingValue);
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
