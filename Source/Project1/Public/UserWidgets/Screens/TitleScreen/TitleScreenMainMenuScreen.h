// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Screens/ScreenUserWidgetBase.h"
#include "TitleScreenMainMenuScreen.generated.h"

class UButtonListComponent;

/**
 *
 */
UCLASS()
class UTitleScreenMainMenuScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButtonListComponent> ButtonListComponent{ nullptr };

	UPROPERTY(EditAnywhere)
	bool bWrapMenuNavigation{ true };

public:
	UTitleScreenMainMenuScreen();

private:
	void NativeOnNavigateTriggered(const FInputActionValue& Value) override;
	void NativeOnConfirmTriggered(const FInputActionValue& Value) override;
	void NativeOnLeftClickTriggered(const FInputActionValue& Value) override;
};
