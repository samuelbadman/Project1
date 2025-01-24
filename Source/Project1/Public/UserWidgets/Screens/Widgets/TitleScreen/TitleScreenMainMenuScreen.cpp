// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenMainMenuScreen.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/TitleScreenPlayerController.h"
#include "InputActionValue.h"

void UTitleScreenMainMenuScreen::NativeOnPushedToLayerStack()
{
	TitleScreenPlayerController = CastChecked<ATitleScreenPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	TitleScreenPlayerController->AddMainMenuUIInputMappingContext();

	// Register events
	MainMenuUIConfirmTriggeredDelegateHandle = TitleScreenPlayerController->MainMenuUIConfirmTriggered.AddUObject(this, &UTitleScreenMainMenuScreen::OnMainMenuUIConfirmTriggered);
	MainMenuUINavigateTriggeredDelegateHandle = TitleScreenPlayerController->MainMenuUINavigateTriggered.AddUObject(this, &UTitleScreenMainMenuScreen::OnMainMenuUINavigateTriggered);
}

void UTitleScreenMainMenuScreen::NativeOnPoppedFromLayerStack()
{
	TitleScreenPlayerController->RemoveMainMenuUIInputMappingContext();

	// Unregister events
	TitleScreenPlayerController->MainMenuUIConfirmTriggered.Remove(MainMenuUIConfirmTriggeredDelegateHandle);
	MainMenuUIConfirmTriggeredDelegateHandle.Reset();

	TitleScreenPlayerController->MainMenuUINavigateTriggered.Remove(MainMenuUINavigateTriggeredDelegateHandle);
	MainMenuUINavigateTriggeredDelegateHandle.Reset();
}

void UTitleScreenMainMenuScreen::OnMainMenuUIConfirmTriggered(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, FString::Printf(TEXT("Main menu UI confirm triggered")));
}

void UTitleScreenMainMenuScreen::OnMainMenuUINavigateTriggered(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, FString::Printf(TEXT("Main menu UI navigate triggered %s"), *Value.Get<FVector2D>().ToString()));
}
