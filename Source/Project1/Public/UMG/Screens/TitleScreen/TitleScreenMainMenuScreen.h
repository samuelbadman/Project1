// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/ScreenUserWidgetBase.h"
#include "TitleScreenMainMenuScreen.generated.h"

class ATitleScreenPlayerController;
struct FInputActionValue;
class UScrollBox;
class UButtonMenuComponent;

/**
 *
 */
UCLASS()
class UTitleScreenMainMenuScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButtonMenuComponent> ButtonMenuComponent;

	TObjectPtr<ATitleScreenPlayerController> TitleScreenPlayerController{ nullptr };

	FDelegateHandle MainMenuUIConfirmTriggeredDelegateHandle{};
	FDelegateHandle MainMenuUINavigateTriggeredDelegateHandle{};

public:
	UTitleScreenMainMenuScreen();

	UFUNCTION(BlueprintImplementableEvent)
	UScrollBox* GetScrollBox();

private:
	void NativeOnPushedToLayerStack() override;
	void NativeOnPoppedFromLayerStack() override;

	void OnMainMenuScreenConfirmTriggered(const FInputActionValue& Value);
	void OnMainMenuScreenNavigateTriggered(const FInputActionValue& Value);
};
