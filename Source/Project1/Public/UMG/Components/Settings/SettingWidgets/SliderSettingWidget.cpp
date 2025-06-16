// Fill out your copyright notice in the Description page of Project Settings.


#include "SliderSettingWidget.h"
#include "Components/Spacer.h"
#include "Components/HorizontalBoxSlot.h"
#include "UMG/Components/Buttons/Project1ButtonBase.h"

void USliderSettingWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	// Update padding of spacer between label and spacer
	if (const TObjectPtr<USpacer> Spacer = GetLabelSpacer())
	{
		CastChecked<UHorizontalBoxSlot>(Spacer->Slot)->SetPadding(LabelMargin);
	}
}

void USliderSettingWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GetSliderHeadButton()->OnClicked.AddDynamic(this, &USliderSettingWidget::OnSliderHeadButtonClicked);
	GetSliderHeadButton()->OnReleased.AddDynamic(this, &USliderSettingWidget::OnSliderHeadButtonReleased);
}

void USliderSettingWidget::OnSliderHeadButtonClicked(UProject1ButtonBase* ButtonClicked)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("Slider head button clicked")));
}

void USliderSettingWidget::OnSliderHeadButtonReleased(UProject1ButtonBase* ButtonReleased)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("Slider head button released")));
}
