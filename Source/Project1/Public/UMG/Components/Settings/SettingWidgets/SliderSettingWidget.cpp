// Fill out your copyright notice in the Description page of Project Settings.


#include "SliderSettingWidget.h"
#include "Components/Spacer.h"
#include "Components/HorizontalBoxSlot.h"

void USliderSettingWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	// Update padding of spacer between label and spacer
	if (const TObjectPtr<USpacer> Spacer = GetLabelSpacer())
	{
		CastChecked<UHorizontalBoxSlot>(Spacer->Slot)->SetPadding(LabelMargin);
	}
}
