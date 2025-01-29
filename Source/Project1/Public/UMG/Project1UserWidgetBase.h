// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Project1UserWidgetBase.generated.h"

enum class EWidgetNavigationDirection : uint8
{
	Up,
	Down,
	Left,
	Right
};

/**
 * 
 */
UCLASS()
class PROJECT1_API UProject1UserWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Project 1 Widget Navigation", meta = (DisplayThumbnail = "false", ShowOnlyInnerProperties))
	TObjectPtr<UWidget> NavigateUpWidget{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Project 1 Widget Navigation", meta = (DisplayThumbnail = "false", ShowOnlyInnerProperties))
	TObjectPtr<UWidget> NavigateDownWidget{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Project 1 Widget Navigation", meta = (DisplayThumbnail = "false", ShowOnlyInnerProperties))
	TObjectPtr<UWidget> NavigateLeftWidget{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Project 1 Widget Navigation", meta = (DisplayThumbnail = "false", ShowOnlyInnerProperties))
	TObjectPtr<UWidget> NavigateRightWidget{ nullptr };

public:
	bool IsCursorInsideWidgetGeometry(const FVector2D& MousePosition) const;

	TWeakObjectPtr<UWidget> GetNavigatedWidget(EWidgetNavigationDirection Direction) const;
	void SetNavigationWidget(EWidgetNavigationDirection Direction, TObjectPtr<UWidget> Widget);
};
