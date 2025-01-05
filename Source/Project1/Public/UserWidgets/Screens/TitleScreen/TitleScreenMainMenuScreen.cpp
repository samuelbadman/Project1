// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenMainMenuScreen.h"
#include "ProjectInput/UserInterfaceInput/UIInputActionValue.h"

void UTitleScreenMainMenuScreen::SetupUIInputActionEvents()
{
	BindUIInputActionEvent(CancelUIInputAction, this, &UTitleScreenMainMenuScreen::OnCancelUIInputTriggered);
}

void UTitleScreenMainMenuScreen::OnCancelUIInputTriggered(const FUIInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("TItleScreen MainMenuScreen Cancel input")));
}
