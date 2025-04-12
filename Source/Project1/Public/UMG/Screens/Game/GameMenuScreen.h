// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/ScreenUserWidgetBase.h"
#include "GameMenuScreen.generated.h"

class AGamePlayerController;
class AGameHUD;
class AGameGameMode;
struct FInputActionValue;
class UProject1ButtonBase;
class UButtonMenuComponent;
class UTextBlock;

/**
 *
 */
UCLASS()
class PROJECT1_API UGameMenuScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButtonMenuComponent> ButtonMenuComponent;

	TObjectPtr<AGamePlayerController> GamePlayerController;
	TObjectPtr<AGameHUD> GameHUD;
	TObjectPtr<AGameGameMode> GameGameMode;
	FDelegateHandle QuitDelegateHandle;
	FDelegateHandle ConfirmDelegateHandle;
	FDelegateHandle NavigateDelegateHandle;
	FDelegateHandle CancelDelegateHandle;

public:
	UGameMenuScreen();

	UFUNCTION(BlueprintImplementableEvent, Category = "TotalPlayTime")
	UTextBlock* GetTotalPlayTimeTextBlock();

private:
	void NativeOnPushedToLayerStack() override;
	void NativeOnPoppedFromLayerStack() override;
	void NativeOnShown() override;
	void NativeOnCollapsed() override;

	void OnQuitTriggered(const FInputActionValue& Value);
	void OnConfirmTriggered(const FInputActionValue& Value);
	void OnNavigateTriggered(const FInputActionValue& Value);
	void OnCancelTriggered(const FInputActionValue& Value);

	void AddScreenInputBindings();
	void RemoveScreenInputBindings();

	UFUNCTION()
	void OnGameSecondElapsed(bool GamePaused);

	void UpdateTotalPlayTimeText();
};
