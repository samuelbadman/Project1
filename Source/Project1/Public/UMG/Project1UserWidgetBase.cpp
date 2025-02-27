// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1UserWidgetBase.h"
#include "Blueprint/SlateBlueprintLibrary.h"

bool UProject1UserWidgetBase::IsMouseCursorOverWidgetGeometry(const FVector2D& MousePosition) const
{
	const FGeometry& Geometry = GetCachedGeometry();
	const FVector2D Size{ Geometry.GetAbsoluteSize() };
	FVector2D TopLeftPixel{}, TopLeftViewport{};
	USlateBlueprintLibrary::LocalToViewport(GetWorld(), Geometry, FVector2D(0.0, 0.0), TopLeftPixel, TopLeftViewport);
	const FVector2D BottomRightPixel = FVector2D(TopLeftPixel.X + Size.X, TopLeftPixel.Y + Size.Y);

	return (MousePosition.X > TopLeftPixel.X && MousePosition.X < BottomRightPixel.X &&
		MousePosition.Y > TopLeftPixel.Y && MousePosition.Y < BottomRightPixel.Y);
}

TWeakObjectPtr<UProject1UserWidgetBase> UProject1UserWidgetBase::GetNavigationWidget(EWidgetNavigationDirection Direction) const
{
	switch (Direction)
	{
	case EWidgetNavigationDirection::Up: return NavigateUpWidget; break;
	case EWidgetNavigationDirection::Down: return NavigateDownWidget; break;
	case EWidgetNavigationDirection::Left: return NavigateLeftWidget; break;
	case EWidgetNavigationDirection::Right: return NavigateRightWidget; break;
	}
	return nullptr;
}

void UProject1UserWidgetBase::SetNavigationWidget(EWidgetNavigationDirection Direction, TObjectPtr<UProject1UserWidgetBase> Widget)
{
	switch (Direction)
	{
	case EWidgetNavigationDirection::Up: NavigateUpWidget = Widget; break;
	case EWidgetNavigationDirection::Down: NavigateDownWidget = Widget; break;
	case EWidgetNavigationDirection::Left: NavigateLeftWidget = Widget; break;
	case EWidgetNavigationDirection::Right: NavigateRightWidget = Widget; break;
	}
}

void UProject1UserWidgetBase::NavigateFromWidgetInDirection(EWidgetNavigationDirection Direction)
{
	OnNavigatedFrom();
	GetNavigationWidget(Direction)->OnNavigatedTo();
}

void UProject1UserWidgetBase::OnNavigatedTo()
{
	// Base class implementation is empty
}

void UProject1UserWidgetBase::OnNavigatedFrom()
{
	// Base class implementation is empty
}
