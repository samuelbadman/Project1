// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUDs/Project1HUDBase.h"
#include "TitleScreenHUD.generated.h"

class UPrimaryLayoutUserWidgetBase;

/**
 * 
 */
UCLASS()
class PROJECT1_API ATitleScreenHUD : public AProject1HUDBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPrimaryLayoutUserWidgetBase> TitleScreenPrimaryLayoutWidgetClass{ nullptr };

	UPROPERTY(BlueprintReadOnly, meta =(AllowPrivateAccess = "true"))
	TObjectPtr<UPrimaryLayoutUserWidgetBase> TitleScreenPrimaryLayoutWidget{ nullptr };

private:
	void BeginPlay() override;
};
