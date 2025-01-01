// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenUserWidgetBase.h"

void UScreenUserWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetupUIInputActionEvents();
}
