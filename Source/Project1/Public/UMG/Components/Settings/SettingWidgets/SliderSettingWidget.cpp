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
	UpdateSliderValue(NewDefaultValue);
	DefaultSliderValue = SliderValue;
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

	// Save reference to the world
	World = GetWorld();

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
	// NOTE: Not using IsNearlyEqual() here as these should only equal when directly set using SetDefaultSliderValue()
	return SliderValue != DefaultSliderValue;
	//return !FMath::IsNearlyEqual(SliderValue, DefaultSliderValue);
}

ESettingInputResult USliderSettingWidget::ProcessContinuousNavigationInput(const FVector2D& NavigationInput)
{
	// NOTE: This event gets called every frame the navigation input is pressed

	// Only care about horizontal input on the X axis here
	if (NavigationInput.X == 0.0)
	{
		return ESettingInputResult::Unhandled;
	}

	// Add slider value at rate each frame scaled by the sign of the navigation input. Left inputs will result in a negative value and right inputs will result in a positive value
	SetSliderValue(SliderValue + (World->GetDeltaSeconds() * GamepadSliderAdjustmentRate * FMath::Sign(NavigationInput.X)));
	return ESettingInputResult::Handled;
}

void USliderSettingWidget::OnSliderHeadButtonClicked(UProject1ButtonBase* ButtonClicked)
{
	// Get game viewport client and subscribe to mouse moved event
	MouseMovedDelegateHandle = CastChecked<UProject1GameViewportClientBase>(UGameplayStatics::GetGameInstance(this)->GetGameViewportClient())->MouseMoved.AddUObject(this,
		&USliderSettingWidget::OnMouseMoved);

	const TObjectPtr<AProject1PlayerControllerBase> PlayerController{ CastChecked<AProject1PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0)) };
	// Flag to the player controller that it should not handle mouse events
	PlayerController->SetIgnoreMouseEventsFlag(true);
	// Do not let the button listen to mouse visibility changed events
	SliderHeadButtonWidget->SetEnableMouseVisibilityChangedEventsFlag(false);
	// Hide the cursor while the slider is being held (disabled here in favour of showing the cursor but locking it to the game window)
	//PlayerController->SetMouseCursorVisibility(EMouseCursorVisibility::Hidden, false, false);
	// Show the cursor and lock it to the game viewport
	PlayerController->SetMouseCursorVisibility(EMouseCursorVisibility::Visible, true, false);
}

void USliderSettingWidget::OnSliderHeadButtonReleased(UProject1ButtonBase* ButtonReleased)
{
	// Get game viewport client and unsubscribe from mouse moved event
	CastChecked<UProject1GameViewportClientBase>(UGameplayStatics::GetGameInstance(this)->GetGameViewportClient())->MouseMoved.Remove(MouseMovedDelegateHandle);
	MouseMovedDelegateHandle.Reset();

	const TObjectPtr<AProject1PlayerControllerBase> PlayerController{ CastChecked<AProject1PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0)) };
	// Flag to the player controller that it should handle mouse events
	PlayerController->SetIgnoreMouseEventsFlag(false);
	// Allow the button listen to mouse visibility changed events
	SliderHeadButtonWidget->SetEnableMouseVisibilityChangedEventsFlag(true);
	// Show the cursor now that the slider has been released (disabled here in favour of showing the cursor but locking it to the game window)
	//PlayerController->SetMouseCursorVisibility(EMouseCursorVisibility::Visible, false, false);
	// Show the cursor and unlock it from the game viewport
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

		// Keep mouse cursor on the same Y axis and inside slider bar X range
		// Below widget geometry size calculation is copied from project1 user widget base
		//const FGeometry& SliderBarPortionParentWidgetGeometry = SliderBarPortionParentWidget->GetCachedGeometry();
		//const FVector2D Size{ SliderBarPortionParentWidgetGeometry.GetAbsoluteSize() };

		//FVector2D SliderBarPortionParentWidgetTopLeftPixel{}, SliderBarPortionParentWidgetTopLeftViewport{};
		//USlateBlueprintLibrary::LocalToViewport(GetWorld(), SliderBarPortionParentWidgetGeometry, FVector2D(0.0, 0.0),
		//	SliderBarPortionParentWidgetTopLeftPixel, SliderBarPortionParentWidgetTopLeftViewport);

		//const FVector2D SliderBarPortionParentWidgetBottomRightPixel = FVector2D(SliderBarPortionParentWidgetTopLeftPixel.X + Size.X,
		//	SliderBarPortionParentWidgetTopLeftPixel.Y + Size.Y);

		//UGameplayStatics::GetPlayerController(this, 0)->SetMouseLocation(
		//	FMath::Clamp(NewMousePosition.X, 
		//		SliderBarPortionParentWidgetTopLeftPixel.X, 
		//		SliderBarPortionParentWidgetBottomRightPixel.X + (GetSliderHeadButtonDimensions().X * 0.5 * UWidgetLayoutLibrary::GetViewportScale(GameViewportClient))),
		//	SliderBarPortionParentWidgetTopLeftPixel.Y + (GetSliderHeadButtonDimensions().Y * 0.5 * UWidgetLayoutLibrary::GetViewportScale(GameViewportClient))
		//);

		// Update slider setting value
		SliderValue = GetSliderValue();

		// Broadcast slider setting value changed
		OnSliderValueChangedDelegate.Broadcast(SliderValue);
	}
}

float USliderSettingWidget::GetSliderValueFromRenderTranslation(const double XTranslation) const
{
	// Map render translation value from the min and max render translation range to the min and max slider value range to obtain the current value of the slider
	return UKismetMathLibrary::MapRangeClamped(StaticCast<float>(XTranslation), 0.0f, SliderBarSize, SliderMinValue, SliderMaxValue);
}

void USliderSettingWidget::UpdateSliderValue(const float NewValue)
{
	SliderValue = FMath::Clamp(NewValue, SliderMinValue, SliderMaxValue);

	// Update the slider head button render translation to match new value
	// Map slider value to render translation range set render translation of the slider head button widget
	FWidgetTransform Transform{};
	Transform.Translation.X = StaticCast<double>(UKismetMathLibrary::MapRangeClamped(NewValue, SliderMinValue, SliderMaxValue, 0.0f, SliderBarSize));
	SliderHeadButtonWidget->SetRenderTransform(Transform);
}

float USliderSettingWidget::GetSliderValue() const
{
	// Get current render translation of the slider head button widget
	return GetSliderValueFromRenderTranslation(SliderHeadButtonWidget->GetRenderTransform().Translation.X);
}

void USliderSettingWidget::SetSliderValue(float NewValue)
{
	UpdateSliderValue(NewValue);

	// Broadcast slider setting value changed
	OnSliderValueChangedDelegate.Broadcast(SliderValue);
}