// Fill out your copyright notice in the Description page of Project Settings.


#include "CompassBarUserWidget.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCameraManagers/GamePlayerCameraManager.h"
#include "FunctionLibraries/Project1BlueprintFunctionLibrary.h"

void UCompassBarUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	// Get compass bar background image's dynamic material
	BackgroundBarDynamicMaterialInstance = GetBackgroundImage()->GetDynamicMaterial();

	// Get game player camera manager
	PlayerCameraManager = CastChecked<AGamePlayerCameraManager>(UGameplayStatics::GetPlayerCameraManager(this, 0));

	// Add player camera updated callback to player camera manager
	PlayerCameraUpdatedDelegateHandle =	PlayerCameraManager->OnCameraUpdated.AddUObject(this, &UCompassBarUserWidget::OnPlayerCameraUpdated);
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
	// Set background bar image material scroll U offset
	BackgroundBarDynamicMaterialInstance->SetScalarParameterValue(ScrollUAxisMaterialParameterName, 
		UProject1BlueprintFunctionLibrary::Normalize360DegreesAngle(UProject1BlueprintFunctionLibrary::ConvertEulerAngleTo360Degrees(CurrentYaw)));
}
