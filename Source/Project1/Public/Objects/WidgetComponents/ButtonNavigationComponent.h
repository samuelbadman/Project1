// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ButtonNavigationComponent.generated.h"

class UProject1ButtonBase;
enum class EWidgetNavigationDirection : uint8;

/**
 * 
 */
UCLASS()
class PROJECT1_API UButtonNavigationComponent : public UObject
{
	GENERATED_BODY()
	
private:
	TObjectPtr<UProject1ButtonBase> CurrentHoveredButton{ nullptr };

public:
	void SetCurrentHoveredButton(TObjectPtr<UProject1ButtonBase> NewHoveredButton, bool MakeNewHoveredButtonHovered = true);

	// Returns the button navigated to in the passed direction else null if navigation failed
	TObjectPtr<UProject1ButtonBase> NavigateButton(EWidgetNavigationDirection Direction);
	bool IsCurrentHoveredButtonValid() const;

	FORCEINLINE TObjectPtr<UProject1ButtonBase> GetCurrentHoveredButton() const { return CurrentHoveredButton; }
};
