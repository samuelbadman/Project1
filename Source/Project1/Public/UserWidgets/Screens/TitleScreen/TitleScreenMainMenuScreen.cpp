// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenMainMenuScreen.h"
#include "ProjectInput/UserInterfaceInput/UIInputActionValue.h"

#include "Kismet/GameplayStatics.h"
#include "HUDs/Project1HUDBase.h"

void UTitleScreenMainMenuScreen::SetupUIInputActionEvents()
{
	BindUIInputActionEvent(CancelUIInputAction, this, &UTitleScreenMainMenuScreen::OnCancelUIInput);
}

void UTitleScreenMainMenuScreen::OnCancelUIInput(const FUIInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Main Menu Cancel input")));

	CastChecked<AProject1HUDBase>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD())->PopContentFromPrimaryLayoutLayer(GetOwningLayerName());
}
