// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Project1UserWidgetBase.h"
#include "ScrollingTextBlock.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class PROJECT1_API UScrollingTextBlock : public UProject1UserWidgetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	FText TextValue;

	UPROPERTY(EditAnywhere)
	FSlateColor TextColorAndOpacity;

	UPROPERTY(EditAnywhere)
	FSlateFontInfo TextFont;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ETextJustify::Type> TextJustification;

	TObjectPtr<UTextBlock> TextBlock;

public:
	UScrollingTextBlock();

	UFUNCTION(BlueprintImplementableEvent, Category = "ScrollingTextBlock")
	UTextBlock* GetTextBlock();

protected:
	void NativePreConstruct() override;
	void NativeOnInitialized() override;
};
