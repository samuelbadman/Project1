// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllers/Project1PlayerControllerBase.h"
#include "TitleScreenPlayerController.generated.h"

class UProject1UserWidgetBase;

/**
 * 
 */
UCLASS()
class PROJECT1_API ATitleScreenPlayerController : public AProject1PlayerControllerBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UProject1UserWidgetBase> TitleScreenWidgetClass{ nullptr };

	TObjectPtr<UProject1UserWidgetBase> TitleScreenWidget{ nullptr };

private:
	void BeginPlay() override;
	void ReceiveAnyKeyInput(const FKey& Key, EInputEvent InputEvent) override;
};
