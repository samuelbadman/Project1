// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenUserWidgetBase.h"

void UScreenUserWidgetBase::SetOwningLayerName(const FGameplayTag& LayerName)
{
	OwningLayerName = LayerName;
}

void UScreenUserWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Project1PlayerController = CastChecked<AProject1PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	Project1HUD = CastChecked<AProject1HUDBase>(Project1PlayerController->GetHUD());
	Project1GameInstance = CastChecked<UProject1GameInstanceBase>(UGameplayStatics::GetGameInstance(this));

	SetupUIInputActionEvents();
}
