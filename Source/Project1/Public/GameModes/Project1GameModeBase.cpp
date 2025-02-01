// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "HUDs/Project1HUDBase.h"

void AProject1GameModeBase::StartPlay()
{
	// Create primary layout widget before beginning play on actors to ensure UI screen widgets are valid if necessary during actor begin play
	TObjectPtr<AProject1HUDBase> Project1HUD{ CastChecked<AProject1HUDBase>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()) };
	Project1HUD->CreatePrimaryLayoutWidget();


	// Parent calls calls begin play on actors
	Super::StartPlay();
}
