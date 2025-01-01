// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenUserWidgetBase.h"

void UScreenUserWidgetBase::OnRawInput(const FKey& Key, EInputEvent InputEvent)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, FString::Printf(TEXT("Raw UI input: Key %s, InputEvent %s"),
		*Key.GetDisplayName().ToString(), *UEnum::GetDisplayValueAsText(InputEvent).ToString()));
}

void UScreenUserWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetupUIInputActionEvents();
}
