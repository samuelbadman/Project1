// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadScreen.h"
#include "Objects/ScreenLoadPayloads/SaveLoadScreenLoadPayload.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/PlayerControllers/Project1PlayerControllerBase.h"
#include "Components/ActorComponents/UIInputComponent.h"
#include "Objects/UIInput/Inputs/SaveLoadScreenUIInput.h"
#include "InputActionValue.h"

USaveLoadScreen::USaveLoadScreen()
	:
	UIInputKey({}),
	bInSaveMode(true),
	SaveLoadScreenUIInput(nullptr),
	CancelInputDelegateHandle({}),
	ConfirmInputDelegateHandle({}),
	NavigateInputDelegateHandle({})
{
}

void USaveLoadScreen::NativeConsumeLoadPayload(TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayload)
{
	Super::NativeConsumeLoadPayload(LoadPayload);

	const TObjectPtr<USaveLoadScreenLoadPayload> Payload{ Cast<USaveLoadScreenLoadPayload>(LoadPayload) };
	bInSaveMode = Payload->bSaving;
}

void USaveLoadScreen::NativeOnPushedToLayerStack()
{
	Super::NativeOnPushedToLayerStack();

	PlayerController = CastChecked<AProject1PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	SaveLoadScreenUIInput = PlayerController->GetUIInputComponent()->GetUIInputAs<USaveLoadScreenUIInput>(UIInputKey);

	// Bind to UI input delegate events
	CancelInputDelegateHandle = SaveLoadScreenUIInput->OnCancelInputTriggeredDelegate.AddUObject(this, &USaveLoadScreen::OnCancelInputTriggered);
	ConfirmInputDelegateHandle = SaveLoadScreenUIInput->OnConfirmInputTriggeredDelegate.AddUObject(this, &USaveLoadScreen::OnConfirmInputTriggered);
	NavigateInputDelegateHandle = SaveLoadScreenUIInput->OnNavigateInputTriggeredDelegate.AddUObject(this, &USaveLoadScreen::OnNavigateInputTriggered);

	SaveLoadScreenUIInput->Add(PlayerController->GetEnhancedInputLocalPlayerSubsystem());
}

void USaveLoadScreen::NativeOnPoppedFromLayerStack()
{
	SaveLoadScreenUIInput->OnCancelInputTriggeredDelegate.Remove(CancelInputDelegateHandle);
	CancelInputDelegateHandle.Reset();

	SaveLoadScreenUIInput->OnConfirmInputTriggeredDelegate.Remove(ConfirmInputDelegateHandle);
	ConfirmInputDelegateHandle.Reset();

	SaveLoadScreenUIInput->OnNavigateInputTriggeredDelegate.Remove(NavigateInputDelegateHandle);
	NavigateInputDelegateHandle.Reset();

	SaveLoadScreenUIInput->Remove(PlayerController->GetEnhancedInputLocalPlayerSubsystem());
}

void USaveLoadScreen::OnCancelInputTriggered(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		CastChecked<AProject1HUDBase>(PlayerController->GetHUD())->PopContentFromPrimaryLayoutWidgetLayer(GetOwningLayerName());
	}
}

void USaveLoadScreen::OnConfirmInputTriggered(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Save load screen Confirm input triggered")));
	}
}

void USaveLoadScreen::OnNavigateInputTriggered(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Save load screen Navigate input triggered: %s"), *Value.Get<FVector2D>().ToString()));
	}
}
