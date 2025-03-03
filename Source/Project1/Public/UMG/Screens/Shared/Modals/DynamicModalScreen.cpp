// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicModalScreen.h"
#include "Objects/ScreenLoadPayloads/DynamicModalScreenLoadPayload.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/Spacer.h"
#include "UMG/Components/DynamicModal/DynamicModalOptionUserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "UMG/Components/Buttons/Project1ButtonBase.h"
#include "PlayerControllers/Project1PlayerControllerBase.h"
#include "InputActionValue.h"
#include "Objects/UserWidgetComponents/ButtonMenuComponent.h"

UDynamicModalScreen::UDynamicModalScreen()
{
	ButtonMenuComponent = CreateDefaultSubobject<UButtonMenuComponent>(FName(TEXT("ButtonMenuComponent")));
}

void UDynamicModalScreen::NativeOnPushedToLayerStack()
{
	// Get project player controller
	Project1PlayerController = CastChecked<AProject1PlayerControllerBase>(GetOwningLocalPlayer()->GetPlayerController(GetWorld()));

	// Bind to modal inputs
	OnConfirmTriggeredDelegateHandle = Project1PlayerController->DynamicModalConfirmTriggered.AddUObject(this, &UDynamicModalScreen::OnConfirmTriggered);
	OnNavigateTriggeredDelegateHandle = Project1PlayerController->DynamicModalNavigateTriggered.AddUObject(this, &UDynamicModalScreen::OnNavigateTriggered);

	// Add modal inputs
	Project1PlayerController->AddDynamicModalInputMappingContext();
}

void UDynamicModalScreen::NativeOnPoppedFromLayerStack()
{
	// Unbind from modal inputs
	Project1PlayerController->DynamicModalConfirmTriggered.Remove(OnConfirmTriggeredDelegateHandle);
	OnConfirmTriggeredDelegateHandle.Reset();

	Project1PlayerController->DynamicModalNavigateTriggered.Remove(OnNavigateTriggeredDelegateHandle);
	OnNavigateTriggeredDelegateHandle.Reset();

	// Remove modal inputs
	Project1PlayerController->RemoveDynamicModalInputMappingContext();
}

void UDynamicModalScreen::NativeConsumeLoadPayload(TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayload)
{
	const TObjectPtr<UDynamicModalScreenLoadPayload> Payload{ CastChecked<UDynamicModalScreenLoadPayload>(LoadPayload) };

	// Set modal prompt text in widget
	SetModalPromptText(Payload->ModalPromptText);

	// Add options to option container
	// Blocking load of option widget class
	const TSubclassOf<UDynamicModalOptionUserWidget> OptionClass{ DynamicModalOptionWidgetClass.LoadSynchronous() };
	if (IsValid(OptionClass))
	{
		const TObjectPtr<APlayerController> WidgetOwningController{ GetOwningLocalPlayer()->GetPlayerController(GetWorld()) };

		const TObjectPtr<UVerticalBox> OptionContainer{ GetDynamicOptionContainer() };

		// For each option
		const int32 NumOptions{ Payload->Options.Num() };
		ModalOptions.Reserve(NumOptions);
		{
			TArray<TObjectPtr<UProject1ButtonBase>> OptionButtons{};
			OptionButtons.Reserve(Payload->Options.Num());

			int32 OptionIndex{ 0 };
			for (const FDynamicModalOptionData& OptionData : Payload->Options)
			{
				// Setup option widget
				// Create option widget
				const TObjectPtr<UDynamicModalOptionUserWidget> OptionWidget{ CreateWidget<UDynamicModalOptionUserWidget>(WidgetOwningController, OptionClass) };

				// Set text label on the option widget
				OptionWidget->SetOptionText(OptionData.OptionText);

				// Setup option button
				const TObjectPtr<UProject1ButtonBase> OptionButton{ OptionWidget->GetButton() };
				OptionButtons.Add(OptionButton);

				// Register button pressed/clicked events
				OptionButton->OnPressed.AddDynamic(this, &UDynamicModalScreen::OnOptionButtonSelected);
				OptionButton->OnClicked.AddDynamic(this, &UDynamicModalScreen::OnOptionButtonSelected);

				// Add the option widget to the option container widget
				OptionContainer->AddChild(OptionWidget);

				// Save modal option alongside its selected delegate
				ModalOptions.Add({ OptionWidget, OptionData.OptionSelectedDelegate });

				// Add spacer widget unless last option being added to add space between each option
				if (OptionIndex < (NumOptions - 1))
				{
					const TObjectPtr<USpacer> Spacer{ WidgetTree->ConstructWidget<USpacer>() };
					const TObjectPtr<UVerticalBoxSlot> SpacerVBoxSlot{ CastChecked<UVerticalBoxSlot>(OptionContainer->AddChild(Spacer)) };
					SpacerVBoxSlot->SetPadding(OptionSpacerPadding);
				}

				++OptionIndex;
			}

			ButtonMenuComponent->RegisterMenuButtons(OptionButtons, false);
			ButtonMenuComponent->SetUnfocusButtonOnMouseCursorLeave(false);

			// Hover first option by default
			ButtonMenuComponent->FocusButton(OptionButtons[0]);
		}

		// Setup button navigation
		const int32 FirstOptionIndex{ 0 };
		const int32 LastOptionIndex{ NumOptions - 1 };

		for (int32 i = 0; i < NumOptions; ++i)
		{
			const TObjectPtr<UProject1ButtonBase> OptionButton{ ModalOptions[i].Key->GetButton() };

			// Setting up direction navigation widget to null. Set to option button at last index if wrapping is desired
			OptionButton->SetNavigationWidget(EWidgetNavigationDirection::Up, (i == FirstOptionIndex) ?
				nullptr : ModalOptions[i - 1].Key->GetButton()
			);

			// Setting down direction navigation widget to null. Set to option button at first index if wrapping is desired
			OptionButton->SetNavigationWidget(EWidgetNavigationDirection::Down, (i == LastOptionIndex) ?
				nullptr : ModalOptions[i + 1].Key->GetButton()
			);
		}
	}
}

void UDynamicModalScreen::OnConfirmTriggered(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		ButtonMenuComponent->PressFocusedButton();
	}
}

void UDynamicModalScreen::OnNavigateTriggered(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		// Only care about horizontal navigation
		const float VerticalInput{ StaticCast<float>(Value.Get<FVector2D>().Y) };

		if (VerticalInput == 0.0f)
		{
			return;
		}

		ButtonMenuComponent->OnNavigationInput((VerticalInput > 0) ? EWidgetNavigationDirection::Up : EWidgetNavigationDirection::Down);
	}
}

void UDynamicModalScreen::OnOptionButtonSelected(UProject1ButtonBase* ButtonSelected)
{
	// Find option with selected button, then call the on selected delegate saved with the option
	auto* const Element{ ModalOptions.FindByPredicate([ButtonSelected](const TPair<TObjectPtr<UDynamicModalOptionUserWidget>, FDynamicModalOptionSelectedDelegate>& A) {
		return A.Key->GetButton() == ButtonSelected;
		}) };

	Element->Value.ExecuteIfBound();
}
