// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadScreen.h"
#include "Objects/ScreenLoadPayloads/SaveLoadScreenLoadPayload.h"

void USaveLoadScreen::NativeConsumeLoadPayload(TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayload)
{
	Super::NativeConsumeLoadPayload(LoadPayload);

	const TObjectPtr<USaveLoadScreenLoadPayload> Payload{ Cast<USaveLoadScreenLoadPayload>(LoadPayload) };
	bInSaveMode = Payload->bSaving;
}

void USaveLoadScreen::NativeOnPushedToLayerStack()
{
	Super::NativeOnPushedToLayerStack();

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("SaveLoadScreen is %s"), (bInSaveMode) ? *FString(TEXT("saving")) : *FString(TEXT("loading"))));
}
