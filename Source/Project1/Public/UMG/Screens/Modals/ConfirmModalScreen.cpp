// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfirmModalScreen.h"
#include "UMG/Components/Buttons/Project1ButtonBase.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/Project1PlayerControllerBase.h"
#include "InputActionValue.h"

UConfirmModalScreen::UConfirmModalScreen()
{
}

void UConfirmModalScreen::NativeOnPushedToLayerStack()
{
	// Setup option buttons
	const TArray<UProject1ButtonBase*> OptionButtons(std::initializer_list<UProject1ButtonBase*>{GetOption1Button(), GetOption2Button()});
	for (UProject1ButtonBase* Button : OptionButtons)
	{
		Button->OnHovered.AddDynamic(this, &UConfirmModalScreen::OnOptionButtonHovered);
		//Button->SetCanMouseUnhoverButton(false); Probable want to use on mouse entered above?
	}

	// Register button pressed/clicked events
	OptionButtons[0]->OnPressed.AddDynamic(this, &UConfirmModalScreen::OnOption1Selected);
	OptionButtons[0]->OnClicked.AddDynamic(this, &UConfirmModalScreen::OnOption1Selected);

	OptionButtons[1]->OnPressed.AddDynamic(this, &UConfirmModalScreen::OnOption2Selected);
	OptionButtons[1]->OnClicked.AddDynamic(this, &UConfirmModalScreen::OnOption2Selected);

	// Hover option 1 by default
	//ButtonNavigationComponent->SetCurrentHoveredButton(OptionButtons[0]);

	// Get player controller
	Project1PlayerController = CastChecked<AProject1PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	// Register to confirm modal inputs
	ConfirmInputTriggeredDelegateHandle = Project1PlayerController->ConfirmModalConfirmTriggered.AddUObject(this, &UConfirmModalScreen::OnConfirmInputTriggered);
	NavigateInputTriggeredDelegateHandle = Project1PlayerController->ConfirmModalNavigateTriggered.AddUObject(this, &UConfirmModalScreen::OnNavigateInputTriggered);

	// Add confirm modal inputs
	Project1PlayerController->AddConfirmModalInputMappingContext();
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
	Project1PlayerController->ConfirmModalConfirmTriggered.Remove(ConfirmInputTriggeredDelegateHandle);
	ConfirmInputTriggeredDelegateHandle.Reset();

	Project1PlayerController->ConfirmModalConfirmTriggered.Remove(NavigateInputTriggeredDelegateHandle);
	NavigateInputTriggeredDelegateHandle.Reset();

	// Remove confirm modal inputs
	Project1PlayerController->RemoveConfirmModalInputMappingContext();
}

void UConfirmModalScreen::OnConfirmInputTriggered(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		//ButtonNavigationComponent->GetCurrentHoveredButton()->PressButton();
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

		//const TObjectPtr<UProject1ButtonBase> NavButton{ ButtonNavigationComponent->NavigateButton(NavDirection) };
		//if (IsValid(NavButton))
		//{
		//	ButtonNavigationComponent->SetCurrentHoveredButton(NavButton);
		//}
	}
}

void UConfirmModalScreen::OnOptionButtonHovered(UProject1ButtonBase* ButtonHovered)
{
	//ButtonNavigationComponent->SetCurrentHoveredButton(ButtonHovered, false);
}

void UConfirmModalScreen::OnOption1Selected(UProject1ButtonBase* ButtonSelected)
{
	Option1SelectedDelegate.ExecuteIfBound();
}

void UConfirmModalScreen::OnOption2Selected(UProject1ButtonBase* ButtonSelected)
{
	Option2SelectedDelegate.ExecuteIfBound();
}
