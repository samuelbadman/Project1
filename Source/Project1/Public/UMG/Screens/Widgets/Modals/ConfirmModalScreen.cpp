// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfirmModalScreen.h"
#include "UMG/Screens/ScreenLoadPayloads/ConfirmModalScreenLoadPayload.h"
#include "UMG/Components/Buttons/Project1ButtonBase.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/Project1PlayerControllerBase.h"
#include "InputActionValue.h"
#include "Objects/WidgetComponents/ButtonNavigationComponent.h"

UConfirmModalScreen::UConfirmModalScreen()
{
	ButtonNavigationComponent = CreateDefaultSubobject<UButtonNavigationComponent>(FName(TEXT("ButtonNavigationComponent")));
}

void UConfirmModalScreen::NativeOnPushedToLayerStack()
{
	// Setup option buttons
	const TArray<UProject1ButtonBase*> OptionButtons(std::initializer_list<UProject1ButtonBase*>{GetOption1Button(), GetOption2Button()});
	for (UProject1ButtonBase* Button : OptionButtons)
	{
		Button->OnHovered.AddDynamic(this, &UConfirmModalScreen::OnOptionButtonHovered);
		Button->SetCanMouseUnhoverButton(false);
	}

	// Hover option 1 by default
	ButtonNavigationComponent->SetCurrentHoveredButton(OptionButtons[0]);

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

	// Bind option delegates

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
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, FString::Printf(TEXT("Confirm modal confirm input: %d"), StaticCast<int32>(Value.Get<bool>())));


}

void UConfirmModalScreen::OnNavigateInputTriggered(const FInputActionValue& Value)
{
	// Only care about horizontal navigation
	const float HorizontalInput{ StaticCast<float>(Value.Get<FVector2D>().X) };

	if (HorizontalInput == 0.0f)
	{
		return;
	}

	const EWidgetNavigationDirection NavDirection{ (HorizontalInput > 0) ? EWidgetNavigationDirection::Right : EWidgetNavigationDirection::Left };

	const TObjectPtr<UProject1ButtonBase> NavButton{ ButtonNavigationComponent->NavigateButton(NavDirection) };
	if (IsValid(NavButton))
	{
		ButtonNavigationComponent->SetCurrentHoveredButton(NavButton);
	}
}

void UConfirmModalScreen::OnOptionButtonHovered(UProject1ButtonBase* ButtonHovered)
{
	ButtonNavigationComponent->SetCurrentHoveredButton(ButtonHovered, false);
}
