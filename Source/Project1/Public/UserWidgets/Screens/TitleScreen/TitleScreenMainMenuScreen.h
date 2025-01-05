// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Screens/ScreenUserWidgetBase.h"
#include "TitleScreenMainMenuScreen.generated.h"

class UUIInputAction;

/**
 * 
 */
UCLASS()
class UTitleScreenMainMenuScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UUIInputAction> CancelUIInputAction{ nullptr };

private:
	void SetupUIInputActionEvents() override;

	void OnCancelUIInputTriggered(const FUIInputActionValue& Value);
};
