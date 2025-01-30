// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/ScreenLoadPayloads/ScreenWidgetLoadPayloadBase.h"
#include "DialogueScreenLoadPayload.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UDialogueScreenLoadPayload : public UScreenWidgetLoadPayloadBase
{
	GENERATED_BODY()
	
public:
	FText InitialDialogueLineText{};
};
