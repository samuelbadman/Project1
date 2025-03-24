// Fill out your copyright notice in the Description page of Project Settings.


#include "CompassBarUserWidget.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCameraManagers/GamePlayerCameraManager.h"
#include "FunctionLibraries/Project1MathLibrary.h"
#include "CompassIconUserWidget.h"

UCompassIconUserWidget* UCompassBarUserWidget::AddCompassIcon(UTexture2D* IconTexture, const FSlateColor& IconTint, const FVector& WorldLocation)
{
	// Create icon widget
	const TObjectPtr<UCompassIconUserWidget> IconWidget{ CreateWidget<UCompassIconUserWidget>(UGameplayStatics::GetPlayerController(this, 0), LoadedCompassIconWidgetClass) };

	// Setup icon widget
	IconWidget->SetOwningCompassBar(this);

	IconWidget->SetIconTexture(IconTexture);
	IconWidget->SetIconTint(IconTint);
	IconWidget->SetWorldLocation(WorldLocation);

	// Add icon widget to compass bar overlay and setup overlay slot icon is in
	const TObjectPtr<UOverlaySlot> OverlaySlot{ CastChecked<UOverlaySlot>(GetBarOverlay()->AddChild(IconWidget)) };
	OverlaySlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	OverlaySlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);

	// Save icon widget
	IconWidgets.Add(IconWidget);

	return IconWidget;
}

void UCompassBarUserWidget::RemoveCompassIcon(UCompassIconUserWidget*& IconWidget)
{
	IconWidgets.RemoveSingle(IconWidget);
	IconWidget->RemoveFromParent();
	IconWidget = nullptr;
}

void UCompassBarUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// Load icon widget class
	LoadedCompassIconWidgetClass = CompassIconWidgetClass.LoadSynchronous();

	// Get compass bar background image's dynamic material
	BackgroundBarDynamicMaterialInstance = GetBackgroundImage()->GetDynamicMaterial();

	// Get game player camera manager
	if (PlayerCameraManager = Cast<AGamePlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(this, 0)))
	{
		// Add player camera updated callback to player camera manager
		PlayerCameraUpdatedDelegateHandle = PlayerCameraManager->OnCameraUpdated.AddUObject(this, &UCompassBarUserWidget::OnPlayerCameraUpdated);
	}
}

void UCompassBarUserWidget::NativeDestruct()
{
	// Remove player camera updated callback from player camera manager
	PlayerCameraManager->OnCameraUpdated.Remove(PlayerCameraUpdatedDelegateHandle);
	PlayerCameraUpdatedDelegateHandle.Reset();

	Super::NativeDestruct();
}

void UCompassBarUserWidget::OnPlayerCameraUpdated(float CurrentPitch, float CurrentYaw)
{
	const float BackgroundBarScrollUAxisValue{ UProject1MathLibrary::Normalize360DegreesAngle(UProject1MathLibrary::ConvertEulerAngleTo360Degrees(CurrentYaw)) };

	// Set background bar image material scroll U axis value
	BackgroundBarDynamicMaterialInstance->SetScalarParameterValue(ScrollUAxisMaterialParameterName, BackgroundBarScrollUAxisValue);

	// Update added icons' scroll U axis value
	for (const TObjectPtr<UCompassIconUserWidget>& IconWidget : IconWidgets)
	{
		IconWidget->UpdateIconScrollUAxisValue();
	}
}

float UCompassBarUserWidget::GetCurrentBackgroundBarScrollUOffset() const
{
	return BackgroundBarDynamicMaterialInstance->K2_GetScalarParameterValue(ScrollUAxisMaterialParameterName);
}
