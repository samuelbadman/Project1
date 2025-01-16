// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllers/Project1PlayerControllerBase.h"
#include "TitleScreenPlayerController.generated.h"

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
	void BeginPlay() override;
};
