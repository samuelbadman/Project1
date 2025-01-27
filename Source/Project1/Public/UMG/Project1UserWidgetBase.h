// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Project1UserWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UProject1UserWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	bool IsCursorInsideWidgetGeometry(const FVector2D& MousePosition) const;
};
