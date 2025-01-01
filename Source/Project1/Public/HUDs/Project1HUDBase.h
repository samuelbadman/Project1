// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Project1HUDBase.generated.h"

class UPrimaryLayoutUserWidgetBase;

/**
 * 
 */
UCLASS()
class PROJECT1_API AProject1HUDBase : public AHUD
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPrimaryLayoutUserWidgetBase> PrimaryLayoutWidgetClass{ nullptr };

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPrimaryLayoutUserWidgetBase> PrimaryLayoutWidget{ nullptr };

public:
	// Make virtual to allow sub HUDs to extend input implementation. Possibly to support multiple primary layout widgets?
	void ReceiveRawPlayerInput(const FKey& Key, EInputEvent InputEvent);

private:
	void BeginPlay() override;
};
