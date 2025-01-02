// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenAnyInputPromptScreen.h"
#include "ProjectInput/UserInterfaceInput/UIInputActionValue.h"

void UTitleScreenAnyInputPromptScreen::SetupUIInputActionEvents()
{
	BindUIInputActionEvent(LeftClickUIInputAction, this, &UTitleScreenAnyInputPromptScreen::OnLeftClickUIInput);
}

void UTitleScreenAnyInputPromptScreen::OnLeftClickUIInput(const FUIInputActionValue& Value)
{
	FVector2D d{ Value.Get<FVector2D>() };
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::White, FString::Printf(TEXT("TitleScreen AnyInputPrompt Screen OnLeftClickUIInput called with value: %s"), *d.ToString()));
}
