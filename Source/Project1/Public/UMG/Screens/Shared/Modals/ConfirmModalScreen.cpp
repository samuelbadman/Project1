// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfirmModalScreen.h"
#include "UMG/Components/Buttons/Project1ButtonBase.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/PlayerControllers/Project1PlayerControllerBase.h"
#include "InputActionValue.h"
#include "Objects/UserWidgetComponents/ButtonMenuComponent.h"
#include "Components/ActorComponents/UIInputComponent.h"
#include "Objects/UIInput/Inputs/ConfirmModalScreenUIInput.h"

UConfirmModalScreen::UConfirmModalScreen()
{
	ButtonMenuComponent = CreateDefaultSubobject<UButtonMenuComponent>(FName(TEXT("ButtonMenuComponent")));
}

void UConfirmModalScreen::NativeOnPushedToLayerStack()
{
	// Setup option buttons
	const TArray<UProject1ButtonBase*> OptionButtons(std::initializer_list<UProject1ButtonBase*>{GetOption1Button(), GetOption2Button()});
	ButtonMenuComponent->RegisterMenuButtons(OptionButtons, false);
	ButtonMenuComponent->SetUnfocusButtonOnMouseCursorLeave(false);

	// Register button pressed/clicked events
	OptionButtons[0]->OnPressed.AddDynamic(this, &UConfirmModalScreen::OnOption1Selected);
	OptionButtons[0]->OnClicked.AddDynamic(this, &UConfirmModalScreen::OnOption1Selected);

	OptionButtons[1]->OnPressed.AddDynamic(this, &UConfirmModalScreen::OnOption2Selected);
	OptionButtons[1]->OnClicked.AddDynamic(this, &UConfirmModalScreen::OnOption2Selected);

	// Hover option 1 by default
	ButtonMenuComponent->FocusButton(OptionButtons[0]);

	// Get player controller
	Project1PlayerController = CastChecked<AProject1PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	// Get confirm modal screen UI input
	ConfirmModalUIInput = Project1PlayerController->GetUIInputComponent()->GetUIInputAs<UConfirmModalScreenUIInput>(UIInputKey);

	// Register to confirm modal inputs
	ConfirmInputTriggeredDelegateHandle = ConfirmModalUIInput->ConfirmTriggeredDelegate.AddUObject(this, &UConfirmModalScreen::OnConfirmInputTriggered);
	NavigateInputTriggeredDelegateHandle = ConfirmModalUIInput->NavigateTriggeredDelegate.AddUObject(this, &UConfirmModalScreen::OnNavigateInputTriggered);

	// Add confirm modal inputs
	ConfirmModalUIInput->Add(Project1PlayerController->GetEnhancedInputLocalPlayerSubsystem());
}

void UConfirmModalScreen::NativeConsumeLoadPayload(TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayload)
{
	Super::NativeConsumeLoadPayload(LoadPayload);

	// Set modal text
	const TObjectPtr<UConfirmModalScreenLoadPayload> Payload{ CastChecked<UConfirmModalScreenLoadPayload>(LoadPayload) };
	SetModalPromptText(Payload->ModalPromptText);
	SetOption1Text(Payload->Option1Text);
	SetOption2Text(Payload->Option2Text);

	// Copy option delegates
	Option1SelectedDelegate = Payload->Option1SelectedDelegate;
	Option2SelectedDelegate = Payload->Option2SelectedDelegate;
}

void UConfirmModalScreen::NativeOnPoppedFromLayerStack()
{
	// Unregister confirm modal inputs
	ConfirmModalUIInput->ConfirmTriggeredDelegate.Remove(ConfirmInputTriggeredDelegateHandle);
	ConfirmInputTriggeredDelegateHandle.Reset();

	ConfirmModalUIInput->NavigateTriggeredDelegate.Remove(NavigateInputTriggeredDelegateHandle);
	NavigateInputTriggeredDelegateHandle.Reset();

	// Remove confirm modal inputs
	ConfirmModalUIInput->Remove(Project1PlayerController->GetEnhancedInputLocalPlayerSubsystem());
}

void UConfirmModalScreen::OnConfirmInputTriggered(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		ButtonMenuComponent->PressFocusedButton();
	}
}

void UConfirmModalScreen::OnNavigateInputTriggered(const FInputActionValue& Value)
{
	if(CanReceiveInput())
	{
		// Only care about horizontal navigation
		const float HorizontalInput{ StaticCast<float>(Value.Get<FVector2D>().X) };

		if (HorizontalInput == 0.0f)
		{
			return;
		}

		const EWidgetNavigationDirection NavDirection{ (HorizontalInput > 0) ? EWidgetNavigationDirection::Right : EWidgetNavigationDirection::Left };
		ButtonMenuComponent->NavigateMenu((HorizontalInput > 0) ? EWidgetNavigationDirection::Right : EWidgetNavigationDirection::Left);
	}
}

void UConfirmModalScreen::OnOption1Selected(UProject1ButtonBase* ButtonSelected)
{
	Option1SelectedDelegate.ExecuteIfBound();
}

void UConfirmModalScreen::OnOption2Selected(UProject1ButtonBase* ButtonSelected)
{
	Option2SelectedDelegate.ExecuteIfBound();
}
