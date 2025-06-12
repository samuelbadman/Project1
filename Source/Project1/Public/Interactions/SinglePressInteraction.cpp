// Fill out your copyright notice in the Description page of Project Settings.


#include "SinglePressInteraction.h"

void USinglePressInteraction::OnInteractInputPressed()
{
	OnInteractionStartedDelegate.Broadcast(this);
	CompleteInteraction();
}
