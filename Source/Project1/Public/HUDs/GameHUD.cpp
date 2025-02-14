// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "UMG/Screens/Game/GameHUDScreen.h"
#include "UMG/Screens/Game/GameMenuScreen.h"

AGameHUD::AGameHUD()
{
    GameHUDWidgetLayerName = {};
    GameMenuScreenClass = nullptr;
    GameMenuWidgetLayerName = {};
}

UGameHUDScreen* AGameHUD::GetGameHUDScreen() const
{
    // Assumes the game HUD screen is on top of the game HUD widget layer however, allows null to be returned if it is not
    return Cast<UGameHUDScreen>(PeekPrimaryLayoutWidgetLayer(GameHUDWidgetLayerName));
}

void AGameHUD::OpenGameMenu()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Cyan, FString::Printf(TEXT("Opening game menu")));
    PushContentToPrimaryLayoutWidgetLayer(GameMenuWidgetLayerName, GameMenuScreenClass);
}

void AGameHUD::CloseGameMenu()
{
    GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Cyan, FString::Printf(TEXT("Closing game menu")));
    PopContentFromPrimaryLayoutWidgetLayer(GameMenuWidgetLayerName);
}
