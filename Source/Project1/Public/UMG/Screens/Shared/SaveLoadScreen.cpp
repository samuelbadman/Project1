// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadScreen.h"
#include "Objects/ScreenLoadPayloads/SaveLoadScreenLoadPayload.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/PlayerControllers/Project1PlayerControllerBase.h"
#include "Components/ActorComponents/UIInputComponent.h"
#include "Objects/UIInput/Inputs/SaveLoadScreenUIInput.h"

USaveLoadScreen::USaveLoadScreen()
	:
	UIInputKey({}),
	bInSaveMode(true),
	SaveLoadScreenUIInput(nullptr),
	CancelInputDelegateHandle({})
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

	CancelInputDelegateHandle = SaveLoadScreenUIInput->OnCancelInputTriggeredDelegate.AddUObject(this, &USaveLoadScreen::OnCancelInputTriggered);

	SaveLoadScreenUIInput->Add(PlayerController->GetEnhancedInputLocalPlayerSubsystem());

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, FString::Printf(TEXT("SaveLoadScreen is %s"), (bInSaveMode) ? *FString(TEXT("saving")) : *FString(TEXT("loading"))));
}

void USaveLoadScreen::NativeOnPoppedFromLayerStack()
{
	SaveLoadScreenUIInput->OnCancelInputTriggeredDelegate.Remove(CancelInputDelegateHandle);
	CancelInputDelegateHandle.Reset();

	SaveLoadScreenUIInput->Remove(PlayerController->GetEnhancedInputLocalPlayerSubsystem());
}

void USaveLoadScreen::OnCancelInputTriggered(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		CastChecked<AProject1HUDBase>(PlayerController->GetHUD())->PopContentFromPrimaryLayoutWidgetLayer(GetOwningLayerName());
	}
}
