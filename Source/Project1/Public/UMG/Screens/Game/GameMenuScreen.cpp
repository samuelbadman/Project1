// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMenuScreen.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/GamePlayerController.h"
#include "HUDs/GameHUD.h"

UGameMenuScreen::UGameMenuScreen()
{
	GamePlayerController = nullptr;
	GameHUD = nullptr;
	ConfirmDelegateHandle = {};
	NavigateDelegateHandle = {};
	CancelDelegateHandle = {};
}

void UGameMenuScreen::NativeOnPushedToLayerStack()
{
	GamePlayerController = CastChecked<AGamePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	GameHUD = CastChecked<AGameHUD>(GamePlayerController->GetHUD());
	QuitDelegateHandle = GamePlayerController->GameMenuScreenQuitTriggered.AddUObject(this, &UGameMenuScreen::OnQuitTriggered);
	ConfirmDelegateHandle = GamePlayerController->GameMenuScreenConfirmTriggered.AddUObject(this, &UGameMenuScreen::OnConfirmTriggered);
	NavigateDelegateHandle = GamePlayerController->GameMenuScreenNavigateTriggered.AddUObject(this, &UGameMenuScreen::OnNavigateTriggered);
	CancelDelegateHandle = GamePlayerController->GameMenuScreenCancelTriggered.AddUObject(this, &UGameMenuScreen::OnCancelTriggered);
	GamePlayerController->AddGameMenuInputMappingContext();
}

void UGameMenuScreen::NativeOnPoppedFromLayerStack()
{
	GamePlayerController->GameMenuScreenQuitTriggered.Remove(QuitDelegateHandle);
	QuitDelegateHandle.Reset();
	GamePlayerController->GameMenuScreenConfirmTriggered.Remove(ConfirmDelegateHandle);
	ConfirmDelegateHandle.Reset();
	GamePlayerController->GameMenuScreenNavigateTriggered.Remove(NavigateDelegateHandle);
	NavigateDelegateHandle.Reset();
	GamePlayerController->GameMenuScreenCancelTriggered.Remove(CancelDelegateHandle);
	CancelDelegateHandle.Reset();
	GamePlayerController->RemoveGameMenuInputMappingContext();
}

void UGameMenuScreen::OnQuitTriggered(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, FString::Printf(TEXT("Game menu screen quit")));
	GameHUD->CloseGameMenu();
}

void UGameMenuScreen::OnConfirmTriggered(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, FString::Printf(TEXT("Game menu screen confirm")));
}

void UGameMenuScreen::OnNavigateTriggered(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, FString::Printf(TEXT("Game menu screen navigate")));
}

void UGameMenuScreen::OnCancelTriggered(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, FString::Printf(TEXT("Game menu screen cancel")));
}
