// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Project1PlayerControllerBase.generated.h"

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
	
protected:
	UPROPERTY(EditDefaultsOnly)
	EMouseCursorVisibility DefaultMouseCursorVisibility{ EMouseCursorVisibility::Hidden };

	UPROPERTY(EditDefaultsOnly)
	bool DefaultLockMouseCursorToViewportWhenVisible{ false };

	UPROPERTY(EditDefaultsOnly)
	bool DefaultCenterCursorInViewportOnBecomeVisible{ true };

public:
	void SetMouseCursorVisibility(EMouseCursorVisibility NewVisibility, bool LockMouseCursorToViewportWhenVisible, bool CenterCursorInViewportOnBecomeVisible);
	bool IsMouseCursorVisible() const { return bShowMouseCursor; }

protected:
	void BeginPlay() override;

	virtual void OnMouseCursorVisibilityChanged(EMouseCursorVisibility NewVisibility) {};

private:
	void CenterMouseCursorInViewport();
};
