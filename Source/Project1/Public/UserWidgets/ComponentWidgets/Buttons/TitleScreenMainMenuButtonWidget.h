// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project1ButtonWidgetBase.h"
#include "TitleScreenMainMenuButtonWidget.generated.h"

class UTextBlock;

/**
 *
 */
UCLASS()
class PROJECT1_API UTitleScreenMainMenuButtonWidget : public UProject1ButtonWidgetBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	FText ButtonText{};

	UPROPERTY(EditAnywhere)
	FSlateColor ButtonTextActiveColor{ FColor::Yellow };

	UPROPERTY(EditAnywhere)
	FSlateColor ButtonTextInactiveColor{ FColor::White };

public:
	UTitleScreenMainMenuButtonWidget();

	UFUNCTION(BlueprintImplementableEvent)
	UTextBlock* GetTextBlock() const;

private:
	void NativePreConstruct() override;
	void NativeOnBecomeActive() override;
	void NativeOnEndActive() override;
};
