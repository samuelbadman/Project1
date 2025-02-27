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
	TObjectPtr<UProject1UserWidgetBase> NavigateUpWidget{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Project 1 Widget Navigation", meta = (DisplayThumbnail = "false", ShowOnlyInnerProperties))
	TObjectPtr<UProject1UserWidgetBase> NavigateDownWidget{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Project 1 Widget Navigation", meta = (DisplayThumbnail = "false", ShowOnlyInnerProperties))
	TObjectPtr<UProject1UserWidgetBase> NavigateLeftWidget{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Project 1 Widget Navigation", meta = (DisplayThumbnail = "false", ShowOnlyInnerProperties))
	TObjectPtr<UProject1UserWidgetBase> NavigateRightWidget{ nullptr };

public:
	bool IsMouseCursorOverWidgetGeometry(const FVector2D& MousePosition) const;

	TWeakObjectPtr<UProject1UserWidgetBase> GetNavigationWidget(EWidgetNavigationDirection Direction) const;
	void SetNavigationWidget(EWidgetNavigationDirection Direction, TObjectPtr<UProject1UserWidgetBase> Widget);
	void NavigateFromWidgetInDirection(EWidgetNavigationDirection Direction);

protected:
	virtual void OnNavigatedTo();
	virtual void OnNavigatedFrom();
};
