// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUDs/Project1HUDBase.h"
#include "GameplayTagContainer.h"
#include "GameHUD.generated.h"

class UGameHUDScreen;

/**
 * 
 */
UCLASS()
class PROJECT1_API AGameHUD : public AProject1HUDBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag GameHUDWidgetLayerName{};

public:
	// Returns the game HUD screen. This can return null
	UFUNCTION(BlueprintCallable)
	UGameHUDScreen* GetGameHUDScreen() const;
};
