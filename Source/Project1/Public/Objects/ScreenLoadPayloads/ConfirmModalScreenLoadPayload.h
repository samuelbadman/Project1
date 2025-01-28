// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/ScreenLoadPayloads/ScreenWidgetLoadPayloadBase.h"
#include "ConfirmModalScreenLoadPayload.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_DELEGATE(FConfirmModalOptionSelectedDelegate);

/**
 *
 */
UCLASS()
class PROJECT1_API UConfirmModalScreenLoadPayload : public UScreenWidgetLoadPayloadBase
{
	GENERATED_BODY()

public:
	FText ModalPromptText{};
	FText Option1Text{};
	FText Option2Text{};
	FConfirmModalOptionSelectedDelegate Option1SelectedDelegate{};
	FConfirmModalOptionSelectedDelegate Option2SelectedDelegate{};
};
