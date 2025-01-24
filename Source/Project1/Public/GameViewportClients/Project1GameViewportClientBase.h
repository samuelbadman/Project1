// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "Project1GameViewportClientBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInputDeviceChangedDelegate, bool /* UsingGamepad */);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnMouseMovedDelegate, const FVector2D& /*NewMousePosition*/, const FVector2D& /*OldMousePosition*/, const FVector2D& /*MouseMoveDelta*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInputKeyDelegate, const FInputKeyEventArgs& /* EventArgs */);

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT1_API UProject1GameViewportClientBase : public UGameViewportClient
{
	GENERATED_BODY()
	
public:
	FOnInputDeviceChangedDelegate InputDeviceChanged{};
	FOnMouseMovedDelegate MouseMoved{};
	FOnInputKeyDelegate OnInputKey{};

private:
	UPROPERTY(EditDefaultsOnly)
	float DetectMouseMoveInterval{ 0.000001f };

	FVector2D PreviousMousePosition{ FVector2D::ZeroVector };
	bool bUsingGamepad{ true };
	FTimerHandle DetectMouseMoveTimerHandle{};

protected:
	void Init(struct FWorldContext& WorldContext, UGameInstance* OwningGameInstance, bool bCreateNewAudioDevice = true) override;
	bool InputKey(const FInputKeyEventArgs& EventArgs) override;

private:
	void DetectMouseMove();
	void OnMouseMoved(const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta);
	void UpdateUsingGamepadState(bool GamepadInput);
	void ChangeGamepadState(bool UsingGamepad);
};
