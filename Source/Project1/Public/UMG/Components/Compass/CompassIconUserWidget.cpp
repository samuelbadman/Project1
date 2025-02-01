// Fill out your copyright notice in the Description page of Project Settings.


#include "CompassIconUserWidget.h"
#include "Components/Image.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "FunctionLibraries/Project1BlueprintFunctionLibrary.h"

void UCompassIconUserWidget::SetIconTexture(TObjectPtr<UTexture2D> Texture)
{
	ImageDynamicMaterialInstance->SetTextureParameterValue(IconTextureParameterName, Texture);
}

void UCompassIconUserWidget::SetIconTint(const FSlateColor& Tint)
{
	GetImage()->SetBrushTintColor(Tint);
}

void UCompassIconUserWidget::UpdateIconScrollUAxisValue(float CurrentCompassBarBackgroundScrollUValue)
{
	// Calculate yaw rotation between the player character and the target location
	const double TargetYaw = UKismetMathLibrary::FindLookAtRotation(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation(), TargetWorldLocation).Yaw;

	// Convert target yaw to 0 - 360 degrees range
	const double TargetYaw360 = UProject1BlueprintFunctionLibrary::ConvertEulerAngleTo360Degrees(TargetYaw);

	// Update icon U texture coordinate offset
	ImageDynamicMaterialInstance->SetScalarParameterValue(ScrollUAxisMaterialParameterName,
		(static_cast<float>(UProject1BlueprintFunctionLibrary::Normalize360DegreesAngle(TargetYaw360)) * -1.0f) + CurrentCompassBarBackgroundScrollUValue);
}

void UCompassIconUserWidget::SetWorldLocation(const FVector& WorldLocation)
{
	TargetWorldLocation = WorldLocation;
}

void UCompassIconUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ImageDynamicMaterialInstance = GetImage()->GetDynamicMaterial();
}
