// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/Widgets/Modals/ModalScreenBase.h"
#include "ConfirmModalScreen.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UConfirmModalScreen : public UModalScreenBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetModalPromptText(const FText& Text);

	UFUNCTION(BlueprintImplementableEvent)
	void SetOption1Text(const FText& Text);

	UFUNCTION(BlueprintImplementableEvent)
	void SetOption2Text(const FText& Text);

private:
	void NativeConsumeLoadPayload(TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayload) override;
};
