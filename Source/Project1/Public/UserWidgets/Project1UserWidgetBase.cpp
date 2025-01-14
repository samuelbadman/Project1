// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1UserWidgetBase.h"
#include "Blueprint/SlateBlueprintLibrary.h"

bool UProject1UserWidgetBase::IsMouseOver(const FVector2D& MousePosition) const
{
	const FGeometry& Geometry = GetCachedGeometry();
	const FVector2D Size{ Geometry.GetAbsoluteSize() };
	FVector2D TopLeftPixel{}, TopLeftViewport{};
	USlateBlueprintLibrary::LocalToViewport(GetWorld(), Geometry, FVector2D(0.0, 0.0), TopLeftPixel, TopLeftViewport);
	const FVector2D BottomRightPixel = FVector2D(TopLeftPixel.X + Size.X, TopLeftPixel.Y + Size.Y);

	return (MousePosition.X > TopLeftPixel.X && MousePosition.X < BottomRightPixel.X &&
		MousePosition.Y > TopLeftPixel.Y && MousePosition.Y < BottomRightPixel.Y);
}
