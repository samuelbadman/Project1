// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controllers/PlayerControllers/Project1PlayerControllerBase.h"
#include "TitleScreenPlayerController.generated.h"

class UProject1GameViewportClientBase;

/**
 * 
 */
UCLASS()
class PROJECT1_API ATitleScreenPlayerController : public AProject1PlayerControllerBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	bool bLockMouseToViewportWhenShown{ false };

	UPROPERTY(EditAnywhere)
	bool bCenterMouseInViewportWhenShown{ false };

private:
	TObjectPtr<UProject1GameViewportClientBase> Project1GameViewportClient{ nullptr };
	FDelegateHandle OnMouseMovedDelegateHandle{};
	FDelegateHandle OnInputKeyDelegateHandle{};

private:
	void BeginPlay() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
