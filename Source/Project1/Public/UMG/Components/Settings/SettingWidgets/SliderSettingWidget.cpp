// Fill out your copyright notice in the Description page of Project Settings.


#include "SliderSettingWidget.h"
#include "Components/Spacer.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/SizeBox.h"
#include "UMG/Components/Buttons/Project1ButtonBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameViewportClients/Project1GameViewportClientBase.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void USliderSettingWidget::SetDefaultSliderValue(float NewDefaultValue)
{
	DefaultSliderValue = FMath::Clamp(NewDefaultValue, SliderMinValue, SliderMaxValue);
}

void USliderSettingWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	// Update padding of spacer between label and spacer
	if (const TObjectPtr<USpacer> Spacer = GetLabelSpacer())
	{
		CastChecked<UHorizontalBoxSlot>(Spacer->Slot)->SetPadding(LabelMargin);
	}

	// Update slider bar size box width
	if (const TObjectPtr<USizeBox> SizeBox = GetSliderBarSizeBox())
	{
		SizeBox->SetWidthOverride(SliderBarSize);
	}
}

void USliderSettingWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// Save reference to the slider head button widget and its parent widget
	SliderHeadButtonParentWidget = GetSliderHeadButtonParent();
	SliderHeadButtonWidget = GetSliderHeadButton();

	SliderHeadButtonWidget->OnClicked.AddDynamic(this, &USliderSettingWidget::OnSliderHeadButtonClicked);
	SliderHeadButtonWidget->OnReleased.AddDynamic(this, &USliderSettingWidget::OnSliderHeadButtonReleased);
}

bool USliderSettingWidget::HasSettingValueChanged() const
{
	return SliderValue != DefaultSliderValue;
}

void USliderSettingWidget::OnSliderHeadButtonClicked(UProject1ButtonBase* ButtonClicked)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("Slider head button clicked")));

	// Get game viewport client and subscribe to mouse moved event
	MouseMovedDelegateHandle = CastChecked<UProject1GameViewportClientBase>(UGameplayStatics::GetGameInstance(this)->GetGameViewportClient())->MouseMoved.AddUObject(this,
		&USliderSettingWidget::OnMouseMoved);
}

void USliderSettingWidget::OnSliderHeadButtonReleased(UProject1ButtonBase* ButtonReleased)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("Slider head button released")));

	// Get game viewport client and unsubscribe from mouse moved event
	CastChecked<UProject1GameViewportClientBase>(UGameplayStatics::GetGameInstance(this)->GetGameViewportClient())->MouseMoved.Remove(MouseMovedDelegateHandle);
	MouseMovedDelegateHandle.Reset();
}

void USliderSettingWidget::OnMouseMoved(const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta)
{
	// NOTE: Mouse move inputs are absolute so, no need to account for frame delta time here

	// Get the position of the slider head button parent widget in the viewport
	const FGeometry& Geometry = SliderHeadButtonParentWidget->GetCachedGeometry();
	FVector2D TopLeftPixel{}, TopLeftViewport{}; 
	USlateBlueprintLibrary::LocalToViewport(GetWorld(), Geometry, FVector2D(0.0, 0.0), TopLeftPixel, TopLeftViewport);

	// Get mouse cursor position in the viewport scaled by DPI
	double MouseXScaledByDPI, MouseYScaledByDPI;
	if (UWidgetLayoutLibrary::GetMousePositionScaledByDPI(UGameplayStatics::GetPlayerController(this, 0), MouseXScaledByDPI, MouseYScaledByDPI))
	{
		// Calculate the DPI scaled offset between the mouse cursor position and the viewport position of the slider head button parent widget and use this as the 
		// render translation offset to align the slider head button with the mouse cursor. An offset is added to align the center of the slider head button widget
		// with the mouse cursor instead of the left edge of the widget
		FWidgetTransform Transform{};
		Transform.Translation.X = (MouseXScaledByDPI - (TopLeftViewport.X + StaticCast<double>(GetSliderHeadButtonHalfWidth())));

		SliderHeadButtonWidget->SetRenderTransform(Transform);

		//SetSliderValue(SliderValue + StaticCast<float>(NewMousePosition.X - TopLeftPixel.X) );
	}
}

void USliderSettingWidget::UpdateSliderHeadButtonParentWidgetRenderTranslationOffset() const
{
	FWidgetTransform Transform{};
	Transform.Translation.X = CalculateSliderHeadButtonRenderTranslationXOffset();

	SliderHeadButtonParentWidget->SetRenderTransform(Transform);
}

double USliderSettingWidget::CalculateSliderHeadButtonRenderTranslationXOffset() const
{
	// Find the percentage the slider value is between the min and max slider values
	// Percentage = (Part/Whole) * 100%
	const float Whole{ SliderMaxValue - SliderMinValue };
	const float Part{ SliderValue - SliderMinValue };
	const float Percentage{ (Part / Whole) };

	// Return the offset as the found percent of the whole slider bar size minus half the width of the slider head button widget to put the center of the widget 
	// on the end of the bar instead of the left edge of the widget
	//return (SliderBarSize * Percentage) - (GetSliderHeadButtonWidth() * 0.5f);
	return 0.0f;
}

void USliderSettingWidget::SetSliderValue(float NewValue)
{
	SliderValue = FMath::Clamp(NewValue, SliderMinValue, SliderMaxValue);
	//UpdateSliderHeadButtonParentWidgetRenderTranslationOffset();
}