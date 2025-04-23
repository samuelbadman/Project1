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
	UPROPERTY(EditAnywhere, Category = "Text")
	FText TextValue;

	UPROPERTY(EditAnywhere, Category = "Text")
	FSlateColor TextColorAndOpacity;

	UPROPERTY(EditAnywhere, Category = "Text")
	FSlateFontInfo TextFont;

	UPROPERTY(EditAnywhere, Category = "Text")
	TEnumAsByte<ETextJustify::Type> TextJustification;

	UPROPERTY(EditAnywhere, Category = "Scroll")
	float ScrollRate{ 0.1f };

	TObjectPtr<UWorld> World;
	TObjectPtr<UTextBlock> TextBlock;

	FTimerHandle ScrollTimerHandle;
	FString ScrollProgressString;
	int32 StringCharIndex;

public:
	UScrollingTextBlock();

	UFUNCTION(BlueprintImplementableEvent, Category = "ScrollingTextBlock")
	UTextBlock* GetTextBlock();

	UFUNCTION(BlueprintCallable, Category = "ScrollingTextBlock")
	void BeginScroll();

	UFUNCTION(BlueprintCallable, Category = "ScrollingTextBlock")
	void StopScroll(bool ShowFullText);

	UFUNCTION(BlueprintCallable, Category = "ScrollingTextBlock")
	bool IsScrolling() const;

	UFUNCTION(BlueprintCallable, Category = "ScrollingTextBlock")
	void SetText(const FText& Text);

protected:
	void NativePreConstruct() override;
	void NativeOnInitialized() override;

private:
	void ProgressScroll();
};
