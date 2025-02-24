// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/ScreenUserWidgetBase.h"
#include "GamePauseScreen.generated.h"

class AGamePlayerController;
class AGameHUD;
struct FInputActionValue;
class UProject1ButtonBase;
class UButtonNavigationComponent;

/**
 *
 */
UCLASS()
class PROJECT1_API UGamePauseScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()

private:
	// TODO: Component object pointer is being set to null after constructor. Possibly being overridden by child blueprint construction to default value (nullptr)
	UPROPERTY()
	TObjectPtr<UButtonNavigationComponent> ButtonNavigationComponent;

	TObjectPtr<AGamePlayerController> GamePlayerController;
	TObjectPtr<AGameHUD> GameHUD;
	FDelegateHandle QuitDelegateHandle;
	FDelegateHandle ConfirmDelegateHandle;
	FDelegateHandle NavigateDelegateHandle;
	FDelegateHandle CancelDelegateHandle;

public:
	UGamePauseScreen();

	UFUNCTION(BlueprintCallable)
	void RegisterMenuButtons(const TArray<UProject1ButtonBase*>& Buttons, int32 DefaultHoveredButtonIndex = 0);

private:
	void NativeOnPushedToLayerStack() override;
	void NativeOnPoppedFromLayerStack() override;

	void OnQuitTriggered(const FInputActionValue& Value);
	void OnConfirmTriggered(const FInputActionValue& Value);
	void OnNavigateTriggered(const FInputActionValue& Value);
	void OnCancelTriggered(const FInputActionValue& Value);
};
