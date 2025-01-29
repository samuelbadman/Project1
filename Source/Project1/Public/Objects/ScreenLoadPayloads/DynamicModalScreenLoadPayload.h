// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/ScreenLoadPayloads/ScreenWidgetLoadPayloadBase.h"
#include "DynamicModalScreenLoadPayload.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_DELEGATE(FDynamicModalOptionSelectedDelegate);

USTRUCT(BlueprintType)
struct FDynamicModalOptionData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText OptionText{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDynamicModalOptionSelectedDelegate OptionSelectedDelegate{};
};

/**
 * 
 */
UCLASS()
class PROJECT1_API UDynamicModalScreenLoadPayload : public UScreenWidgetLoadPayloadBase
{
	GENERATED_BODY()
	
public:
	FText ModalPromptText{};
	TArray<FDynamicModalOptionData> Options{};
};
