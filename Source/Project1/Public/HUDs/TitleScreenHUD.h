// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUDs/Project1HUDBase.h"
#include "TitleScreenHUD.generated.h"

class UTitleScreenMasterUserWidget;

/**
 * 
 */
UCLASS()
class PROJECT1_API ATitleScreenHUD : public AProject1HUDBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UTitleScreenMasterUserWidget> TitleScreenMasterWidgetClass{ nullptr };

	TObjectPtr<UTitleScreenMasterUserWidget> TitleScreenMasterWidget{ nullptr };

private:
	void BeginPlay() override;
};
