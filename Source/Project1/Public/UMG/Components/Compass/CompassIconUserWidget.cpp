// Fill out your copyright notice in the Description page of Project Settings.


#include "CompassIconUserWidget.h"
#include "Components/Image.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "FunctionLibraries/Project1BlueprintFunctionLibrary.h"
#include "CompassBarUserWidget.h"

void UCompassIconUserWidget::SetIconTexture(UTexture2D* Texture)
{
	ImageDynamicMaterialInstance->SetTextureParameterValue(IconTextureParameterName, Texture);
}

void UCompassIconUserWidget::SetIconTint(const FSlateColor& Tint)
{
	GetImage()->SetBrushTintColor(Tint);
}

void UCompassIconUserWidget::UpdateIconScrollUAxisValue()
{
	// Calculate yaw rotation between the player character and the target location
	const double TargetYaw = UKismetMathLibrary::FindLookAtRotation(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation(), TargetWorldLocation).Yaw;

	// Convert target yaw to 0 - 360 degrees range
	const double TargetYaw360 = UProject1BlueprintFunctionLibrary::ConvertEulerAngleTo360Degrees(TargetYaw);

	// Update icon U texture coordinate offset
	ImageDynamicMaterialInstance->SetScalarParameterValue(ScrollUAxisMaterialParameterName,
		(static_cast<float>(UProject1BlueprintFunctionLibrary::Normalize360DegreesAngle(TargetYaw360)) * -1.0f) + OwningCompassBar->GetCurrentBackgroundBarScrollUOffset());
}

void UCompassIconUserWidget::SetWorldLocation(const FVector& WorldLocation)
{
	TargetWorldLocation = WorldLocation;
	UpdateIconScrollUAxisValue();
}

void UCompassIconUserWidget::SetOwningCompassBar(TObjectPtr<UCompassBarUserWidget> CompassBar)
{
	OwningCompassBar = CompassBar;
}

void UCompassIconUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ImageDynamicMaterialInstance = GetImage()->GetDynamicMaterial();
}

void UCompassIconUserWidget::BeginDestroy()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, FString::Printf(TEXT("Destroying compass icon: %s"), *GetName()));

	Super::BeginDestroy();
}
