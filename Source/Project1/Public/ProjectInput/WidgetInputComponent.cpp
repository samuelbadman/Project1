// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/Project1PlayerControllerBase.h"

void UWidgetInputComponent::Initialize()
{
	Cast<AProject1PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0))->GetOnPlayerInputDelegate().AddUObject(this, &UWidgetInputComponent::OnPlayerInput);
}

void UWidgetInputComponent::OnPlayerInput(const FKey& Key, EInputEvent InputEvent)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, FString::Printf(TEXT("WidgetInputComponent AnyKeyInput: Key %s, InputEvent %s"),
		*Key.GetDisplayName().ToString(), *UEnum::GetDisplayValueAsText(InputEvent).ToString()));
}
