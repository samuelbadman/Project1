// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Screens/ScreenUserWidgetBase.h"
#include "TitleScreenAnyInputPromptScreen.generated.h"

class UUIInputAction;

/**
 * 
 */
UCLASS()
class UTitleScreenAnyInputPromptScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UUIInputAction> LeftClickUIInputAction{ nullptr };

private:
	void SetupUIInputActionEvents() override;

	void OnLeftClickUIInput(const FUIInputActionValue& Value);
};
