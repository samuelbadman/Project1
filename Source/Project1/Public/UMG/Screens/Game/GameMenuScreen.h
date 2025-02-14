// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/ScreenUserWidgetBase.h"
#include "GameMenuScreen.generated.h"

class AGamePlayerController;
class AGameHUD;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class PROJECT1_API UGameMenuScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()
	
private:
	TObjectPtr<AGamePlayerController> GamePlayerController;
	TObjectPtr<AGameHUD> GameHUD;
	FDelegateHandle QuitDelegateHandle;
	FDelegateHandle ConfirmDelegateHandle;
	FDelegateHandle NavigateDelegateHandle;
	FDelegateHandle CancelDelegateHandle;

private:
	UGameMenuScreen();

	void NativeOnPushedToLayerStack() override;
	void NativeOnPoppedFromLayerStack() override;

	void OnQuitTriggered(const FInputActionValue& Value);
	void OnConfirmTriggered(const FInputActionValue& Value);
	void OnNavigateTriggered(const FInputActionValue& Value);
	void OnCancelTriggered(const FInputActionValue& Value);
};
