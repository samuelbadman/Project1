// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Project1PlayerControllerBase.generated.h"

class UProject1GameInstanceBase;
class AProject1HUDBase;

UENUM()
enum class EMouseCursorVisibility : uint8
{
	Visible,
	Hidden
};

//DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerInputDelegateSignature, const FKey& /* Key */, EInputEvent /* InputEvent */);

/**
 * 
 */
UCLASS()
class PROJECT1_API AProject1PlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	EMouseCursorVisibility DefaultMouseCursorVisibility{ EMouseCursorVisibility::Hidden };

	UPROPERTY(EditDefaultsOnly)
	bool DefaultLockMouseCursorToViewportWhenVisible{ false };

	UPROPERTY(EditDefaultsOnly)
	bool DefaultCenterCursorInViewportOnBecomeVisible{ true };

	//FOnPlayerInputDelegateSignature OnPlayerInputDelegate{};

	TObjectPtr<UProject1GameInstanceBase> ProjectGameInstance{ nullptr };
	TObjectPtr<AProject1HUDBase> ProjectHUD{ nullptr };

public:
	void SetMouseCursorVisibility(EMouseCursorVisibility NewVisibility, bool LockMouseCursorToViewportWhenVisible, bool CenterCursorInViewportOnBecomeVisible);

	//FOnPlayerInputDelegateSignature& GetOnPlayerInputDelegate() { return OnPlayerInputDelegate; }

protected:
	void SetupInputComponent() override;
	void BeginPlay() override;

private:
	void OnAnyKeyInput(const FKey& Key, EInputEvent InputEvent);
	void ReceiveAnyKeyInput(const FKey& Key, EInputEvent InputEvent);
	bool IsMouseCursorVisible() const;
	void CenterMouseCursorInViewport();
};
