// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Project1UserWidgetBase.h"
#include "TitleScreenMasterUserWidget.generated.h"

class UWidgetInputComponent;

/**
 * 
 */
UCLASS()
class PROJECT1_API UTitleScreenMasterUserWidget : public UProject1UserWidgetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	TObjectPtr<UWidgetInputComponent> WidgetInputComponent{ nullptr };

public:
	UTitleScreenMasterUserWidget();

private:
	void NativeOnInitialized() override;
};
