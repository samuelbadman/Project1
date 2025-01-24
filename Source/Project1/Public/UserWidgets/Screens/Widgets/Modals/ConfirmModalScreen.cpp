// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfirmModalScreen.h"
#include "UserWidgets/Screens/ScreenLoadPayloads/ConfirmModalScreenLoadPayload.h"

void UConfirmModalScreen::NativeConsumeLoadPayload(TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayload)
{
	Super::NativeConsumeLoadPayload(LoadPayload);

	// Set modal text
	const TObjectPtr<UConfirmModalScreenLoadPayload> Payload{ CastChecked<UConfirmModalScreenLoadPayload>(LoadPayload) };
	SetModalPromptText(Payload->ModalPromptText);
	SetOption1Text(Payload->Option1Text);
	SetOption2Text(Payload->Option2Text);

	// Bind option delegates

}
