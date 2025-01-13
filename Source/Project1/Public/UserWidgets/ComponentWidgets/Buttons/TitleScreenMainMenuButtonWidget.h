// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project1ButtonWidgetBase.h"
#include "TitleScreenMainMenuButtonWidget.generated.h"

class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActiveConfirmInputDelegateSignature);

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
	FSlateColor ButtonTextActiveColor{FColor::Yellow};

	UPROPERTY(EditAnywhere)
	FSlateColor ButtonTextInactiveColor{FColor::White};

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "On Active Confirm Input"))
	FOnActiveConfirmInputDelegateSignature OnActiveConfirmInputDelegate{};

public:
	UTitleScreenMainMenuButtonWidget();

	UFUNCTION(BlueprintImplementableEvent)
	UTextBlock* GetTextBlock() const;

	void OnBecomeActive();
	void OnEndActive();
	void OnActiveConfirmInput();

private:
	void NativePreConstruct() override;
};
