// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Project1UserWidgetBase.h"
#include "ButtonText.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class PROJECT1_API UButtonText : public UProject1UserWidgetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	FText ButtonTextValue;

public:
	UButtonText();

	UFUNCTION(BlueprintImplementableEvent, Category = "ButtonText")
	UTextBlock* GetTextBlock();

	UFUNCTION(BlueprintCallable, Category = "ButtonText")
	void SetTextValue(const FText& Text);

private:
	void NativePreConstruct() override;
};
