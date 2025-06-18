// Fill out your copyright notice in the Description page of Project Settings.


#include "SliderSettingWidget.h"
#include "Components/Spacer.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/SizeBox.h"
#include "UMG/Components/Buttons/Project1ButtonBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameViewportClients/Project1GameViewportClientBase.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Controllers/PlayerControllers/Project1PlayerControllerBase.h"

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

	// Save reference to the game viewport client
	GameViewportClient = UGameplayStatics::GetGameInstance(this)->GetGameViewportClient();

	// Save reference to the slider head button widget and its parent widget
	SliderHeadButtonParentWidget = GetSliderHeadButtonParent();
	SliderHeadButtonWidget = GetSliderHeadButton();
	SliderBarPortionParentWidget = GetSliderBarPortionParent();

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

	const TObjectPtr<AProject1PlayerControllerBase> PlayerController{ CastChecked<AProject1PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0)) };
	// Flag to the player controller that it should not handle mouse events
	PlayerController->SetIgnoreMouseEventsFlag(true);
	// Do not let the button listen to mouse visibility changed events
	SliderHeadButtonWidget->SetEnableMouseVisibilityChangedEventsFlag(false);
	// Hide the cursor while the slider is being held
	PlayerController->SetMouseCursorVisibility(EMouseCursorVisibility::Hidden, false, false);
}

void USliderSettingWidget::OnSliderHeadButtonReleased(UProject1ButtonBase* ButtonReleased)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("Slider head button released")));

	// Get game viewport client and unsubscribe from mouse moved event
	CastChecked<UProject1GameViewportClientBase>(UGameplayStatics::GetGameInstance(this)->GetGameViewportClient())->MouseMoved.Remove(MouseMovedDelegateHandle);
	MouseMovedDelegateHandle.Reset();

	const TObjectPtr<AProject1PlayerControllerBase> PlayerController{ CastChecked<AProject1PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0)) };
	// Flag to the player controller that it should handle mouse events
	PlayerController->SetIgnoreMouseEventsFlag(false);
	// Allow the button listen to mouse visibility changed events
	SliderHeadButtonWidget->SetEnableMouseVisibilityChangedEventsFlag(true);
	// Show the cursor now that the slider has been released
	PlayerController->SetMouseCursorVisibility(EMouseCursorVisibility::Visible, false, false);
}

void USliderSettingWidget::OnMouseMoved(const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta)
{
	// NOTE: Mouse move inputs are absolute so, no need to account for frame delta time here

	// Get the position of the slider head button parent widget in the viewport
	const FGeometry& SliderHeadButtonParentWidgetGeometry = SliderHeadButtonParentWidget->GetCachedGeometry();
	FVector2D SliderHeadButtonParentWidgetTopLeftPixel{}, SliderHeadButtonParentWidgetTopLeftViewport{};
	USlateBlueprintLibrary::LocalToViewport(GetWorld(), SliderHeadButtonParentWidgetGeometry, FVector2D(0.0, 0.0),
		SliderHeadButtonParentWidgetTopLeftPixel, SliderHeadButtonParentWidgetTopLeftViewport);

	// Get mouse cursor position in the viewport scaled by DPI
	double MouseXScaledByDPI, MouseYScaledByDPI;
	if (UWidgetLayoutLibrary::GetMousePositionScaledByDPI(UGameplayStatics::GetPlayerController(this, 0), MouseXScaledByDPI, MouseYScaledByDPI))
	{
		// Calculate the DPI scaled offset between the mouse cursor position and the viewport position of the slider head button parent widget and use this as the 
		// render translation offset to align the slider head button with the mouse cursor. An offset is added to align the center of the slider head button widget
		// with the mouse cursor instead of the left edge of the widget
		FWidgetTransform Transform{};
		Transform.Translation.X = FMath::Clamp(
			(MouseXScaledByDPI - (SliderHeadButtonParentWidgetTopLeftViewport.X + (GetSliderHeadButtonDimensions().X * 0.5))),
			0.0,
			StaticCast<double>(SliderBarSize)
		);

		SliderHeadButtonWidget->SetRenderTransform(Transform);

		// TODO: On slider value changed. Report new value here

		// Keep mouse cursor on the same Y axis and inside slider bar X range
		// Below is copied from project1 user widget base
		const FGeometry& SliderBarPortionParentWidgetGeometry = SliderBarPortionParentWidget->GetCachedGeometry();
		const FVector2D Size{ SliderBarPortionParentWidgetGeometry.GetAbsoluteSize() };

		FVector2D SliderBarPortionParentWidgetTopLeftPixel{}, SliderBarPortionParentWidgetTopLeftViewport{};
		USlateBlueprintLibrary::LocalToViewport(GetWorld(), SliderBarPortionParentWidgetGeometry, FVector2D(0.0, 0.0),
			SliderBarPortionParentWidgetTopLeftPixel, SliderBarPortionParentWidgetTopLeftViewport);

		const FVector2D SliderBarPortionParentWidgetBottomRightPixel = FVector2D(SliderBarPortionParentWidgetTopLeftPixel.X + Size.X,
			SliderBarPortionParentWidgetTopLeftPixel.Y + Size.Y);

		UGameplayStatics::GetPlayerController(this, 0)->SetMouseLocation(
			FMath::Clamp(NewMousePosition.X, SliderBarPortionParentWidgetTopLeftPixel.X, SliderBarPortionParentWidgetBottomRightPixel.X),
			SliderBarPortionParentWidgetTopLeftPixel.Y + (GetSliderHeadButtonDimensions().X * 0.5 * UWidgetLayoutLibrary::GetViewportScale(GameViewportClient))
		);
	}
}

float USliderSettingWidget::GetSliderValue() const
{
	// Get current render translation of the slider head button widget
	const float RenderTranslation{ StaticCast<float>(SliderHeadButtonWidget->GetRenderTransform().Translation.X) };

	// Map render translation value from the min and max render translation range to the min and max slider value range to obtain the current value of the slider
	return UKismetMathLibrary::MapRangeClamped(RenderTranslation, 0.0f, SliderBarSize, SliderMinValue, SliderMaxValue);
}

void USliderSettingWidget::SetSliderValue(float NewValue)
{
	SliderValue = FMath::Clamp(NewValue, SliderMinValue, SliderMaxValue);

	// Update the slider head button render translation to match new value
	// Map slider value to render translation range set render translation of the slider head button widget
	FWidgetTransform Transform{};
	Transform.Translation.X = StaticCast<double>(UKismetMathLibrary::MapRangeClamped(NewValue, SliderMinValue, SliderMaxValue, 0.0f, SliderBarSize));
	SliderHeadButtonWidget->SetRenderTransform(Transform);
}