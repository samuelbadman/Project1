// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "UMG/Screens/Game/GameHUDScreen.h"
#include "UMG/Screens/Game/GamePauseScreen.h"

AGameHUD::AGameHUD()
{
    GameHUDWidgetLayerName = {};
    GamePauseScreenClass = nullptr;
    GamePauseWidgetLayerName = {};
}

UGameHUDScreen* AGameHUD::GetGameHUDScreen() const
{
    // Assumes the game HUD screen is on top of the game HUD widget layer however, allows null to be returned if it is not
    return Cast<UGameHUDScreen>(PeekPrimaryLayoutWidgetLayer(GameHUDWidgetLayerName));
}

void AGameHUD::OpenGameMenu()
{
    PushContentToPrimaryLayoutWidgetLayer(GamePauseWidgetLayerName, GamePauseScreenClass);
}

void AGameHUD::CloseGameMenu()
{
    PopContentFromPrimaryLayoutWidgetLayer(GamePauseWidgetLayerName);
}

void AGameHUD::SetGameHUDScreenShown(bool Shown)
{
    if (Shown)
    {
        ShowPrimaryLayoutWidgetLayerTop(GameHUDWidgetLayerName);
    }
    else
    {
        CollapsePrimaryLayoutWidgetLayerTop(GameHUDWidgetLayerName);
    }
}
