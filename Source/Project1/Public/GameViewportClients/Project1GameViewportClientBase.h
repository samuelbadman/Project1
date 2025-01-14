// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "Project1GameViewportClientBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInputDeviceChangedDelegateSignature, bool /* UsingGamepad */);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnMouseMovedDelegateSignature, const FVector2D& /*NewMousePosition*/, const FVector2D& /*OldMousePosition*/, const FVector2D& /*MouseMoveDelta*/);

/**
 * 
 */
UCLASS()
class PROJECT1_API UProject1GameViewportClientBase : public UGameViewportClient
{
	GENERATED_BODY()
	
private:
	FVector2D PreviousMousePosition{ FVector2D::ZeroVector };
	bool bUsingGamepad{ true };
	FOnInputDeviceChangedDelegateSignature OnInputDeviceChangedDelegate{};
	FOnMouseMovedDelegateSignature OnMouseMovedDelegate{};

public:
	// The project's game viewport client class can be retrieved from the game instance
	FORCEINLINE FOnInputDeviceChangedDelegateSignature& GetOnInputDeviceChangedDelegate() { return OnInputDeviceChangedDelegate; }
	FORCEINLINE FOnMouseMovedDelegateSignature& GetOnMouseMovedDelegate() { return OnMouseMovedDelegate; }

protected:
	void Tick(float DeltaTime) override;
	bool InputKey(const FInputKeyEventArgs& EventArgs) override;

private:
	bool DetectMouseMove();
	void OnMouseMoved(const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta);
	void UpdateUsingGamepadState(bool GamepadInput);
	void ChangeGamepadState(bool UsingGamepad);
};
