// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "Project1GameViewportClientBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInputDeviceChangedDelegateSignature, bool /* UsingGamepad */);

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

public:
	FORCEINLINE FOnInputDeviceChangedDelegateSignature& GetOnInputDeviceChangedDelegate() { return OnInputDeviceChangedDelegate; }

protected:
	void Tick(float DeltaTime) override;
	bool InputKey(const FInputKeyEventArgs& EventArgs) override;

private:
	bool DetectMouseMove();
	void OnMouseMoved(const FVector2D& MouseMoveDelta);
	void UpdateUsingGamepadState(bool GamepadInput);
	void ChangeGamepadState(bool UsingGamepad);
};
