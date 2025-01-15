// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UIComponentBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UUIComponentBase : public UObject
{
	GENERATED_BODY()
	
private:
	TObjectPtr<UUserWidget> WidgetOwner{ nullptr };

public:
	FORCEINLINE void SetWidgetOwner(TObjectPtr<UUserWidget> Owner) { WidgetOwner = Owner; }
	FORCEINLINE TObjectPtr<UUserWidget> GetWidgetOwner() const { return WidgetOwner; }
};
