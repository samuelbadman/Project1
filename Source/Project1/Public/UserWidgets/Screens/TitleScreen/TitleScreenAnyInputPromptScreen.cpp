// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenAnyInputPromptScreen.h"
#include "ProjectInput/UserInterfaceInput/UIInputActionValue.h"

void UTitleScreenAnyInputPromptScreen::SetupUIInputActionEvents()
{
	BindUIInputActionEvent(AnyInputUIInputAction, this, &UTitleScreenAnyInputPromptScreen::OnAnyInputUIInput);
}

void UTitleScreenAnyInputPromptScreen::OnAnyInputUIInput(const FUIInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, FString::Printf(TEXT("TitleScreen AnyInputPrompt Screen OnAnyInputUIInput called with value: %s"),
		*Value.Get<FVector2D>().ToString()));
}
