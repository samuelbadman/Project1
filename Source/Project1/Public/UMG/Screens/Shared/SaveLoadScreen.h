// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/ScreenUserWidgetBase.h"
#include "SaveLoadScreen.generated.h"

/**
 * 
 */
UCLASS()
class USaveLoadScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()
	
private:
	bool bInSaveMode{ true };

private:
	void NativeConsumeLoadPayload(TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayload) override;
	void NativeOnPushedToLayerStack() override;
};
