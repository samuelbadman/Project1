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

	TObjectPtr<UProject1GameInstanceBase> ProjectGameInstance{ nullptr };
	TObjectPtr<AProject1HUDBase> Project1HUD{ nullptr };

public:
	void SetMouseCursorVisibility(EMouseCursorVisibility NewVisibility, bool LockMouseCursorToViewportWhenVisible, bool CenterCursorInViewportOnBecomeVisible);

protected:
	void BeginPlay() override;

private:
	bool IsMouseCursorVisible() const { return bShowMouseCursor; }
	void CenterMouseCursorInViewport();
};
