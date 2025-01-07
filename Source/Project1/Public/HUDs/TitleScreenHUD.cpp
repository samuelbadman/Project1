// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenHUD.h"

void ATitleScreenHUD::BeginPlay()
{
	Super::BeginPlay();

	// TODO: Delay before adding mapping contexts at the start of the game as held inputs from old levels will trigger pressed inputs that are not wanted
	SetUIInputsEnabled(true);
}
