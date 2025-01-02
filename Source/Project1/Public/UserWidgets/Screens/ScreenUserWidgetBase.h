// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Project1UserWidgetBase.h"
#include "GameplayTagContainer.h"
#include "Kismet/GameplayStatics.h"
#include "HUDs/Project1HUDBase.h"
#include "PlayerControllers/Project1PlayerControllerBase.h"
#include "ProjectInput/UserInterfaceInput/UIInputActionMapping.h"
#include "ProjectInput/UserInterfaceInput/UIInputActionValue.h"
#include "GameInstances/Project1GameInstanceBase.h"
#include "ProjectInput/InputKeyStateController.h"
#include "ScreenUserWidgetBase.generated.h"

class UUIInputAction;
struct FUIInputActionValue;

/**
 *
 */
UCLASS()
class PROJECT1_API UScreenUserWidgetBase : public UProject1UserWidgetBase
{
	GENERATED_BODY()

protected:
	template <typename T>
	void BindUIInputActionEvent(TObjectPtr<UUIInputAction> UIInputAction, T* UserObject, void (T::* Event)(const FUIInputActionValue&))
	{
		// Get keys mapped to input action from input action mapping. The mapping is stored in the primary layout widget that exists in the HUD
		const TObjectPtr<AProject1PlayerControllerBase> PlayerController{ CastChecked<AProject1PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0)) };
		const TObjectPtr<AProject1HUDBase> HUD{ CastChecked<AProject1HUDBase>(PlayerController->GetHUD()) };
		const TObjectPtr<UProject1GameInstanceBase> GameInstance{ CastChecked<UProject1GameInstanceBase>(UGameplayStatics::GetGameInstance(this)) };

		// Get the UI input action mapping. This is where inputs can be disabled by implementing a system that uses multiple input mapping assets with
		// priorities similiar to the enhanced input system
		const TObjectPtr<const UUIInputActionMapping> InputActionMapping{ HUD->GetUIInputActionMapping() };

		if (!IsValid(InputActionMapping))
		{
			return;
		}

		const auto& ActionMapping{ InputActionMapping->GetActionMapping() };

		// For each value mapped to the input action
		const FUIInputActionMappingValue* pActionMappingValue{ ActionMapping.Find(UIInputAction) };
		for (const auto& KeyMapping : pActionMappingValue->Mapping) // KeyMapping is the value of the ActionMapping key value map
		{
			// Bind to input key events for the key in the mapping
			// Pressed binding
			FInputKeyBinding AnyKeyPressedBinding(KeyMapping.Key, EInputEvent::IE_Pressed);
			AnyKeyPressedBinding.bConsumeInput = KeyMapping.bConsumeInput;
			AnyKeyPressedBinding.bExecuteWhenPaused = KeyMapping.bExecuteWhenPaused;
			AnyKeyPressedBinding.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([this, GameInstance, UserObject, Event, KeyMapping](const FKey& Key)
				{
					// The mapped key was pressed
					// Get input key state manager from game instance
					UInputKeyStateController& InputKeyStateController{ GameInstance->GetInputKeyStateController() };

					// Get new key state for the input key
					const EInputKeyState NewKeyState{ InputKeyStateController.GetInputKeyStateFromInputEvent(EInputEvent::IE_Pressed) };

					// If the key is already in the new key state, ignore the input
					if (InputKeyStateController.GetKeyState(Key) == NewKeyState)
					{
						return;
					}

					// Update input key state
					InputKeyStateController.SetKeyState(Key, NewKeyState);

					// Handle the input
					FUIInputActionValue Value{};
					// Determine value
					SetUIInputActionValue(Value, KeyMapping, FUIInputActionValue::PressedValue);

					// Call bound event on screen widget
					(UserObject->*Event)(Value);
				}
			);

			PlayerController->InputComponent->KeyBindings.Add(AnyKeyPressedBinding);

			// Released binding
			FInputKeyBinding AnyKeyReleasedBinding(KeyMapping.Key, EInputEvent::IE_Released);
			AnyKeyReleasedBinding.bConsumeInput = KeyMapping.bConsumeInput;
			AnyKeyReleasedBinding.bExecuteWhenPaused = KeyMapping.bExecuteWhenPaused;
			AnyKeyReleasedBinding.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([this, GameInstance, UserObject, Event, KeyMapping](const FKey& Key)
				{
					// The mapped key was released
					// Get input key state manager from game instance
					UInputKeyStateController& InputKeyStateController{ GameInstance->GetInputKeyStateController() };

					// Get new key state for the input key
					const EInputKeyState NewKeyState{ InputKeyStateController.GetInputKeyStateFromInputEvent(EInputEvent::IE_Released) };

					// If the key is already in the new key state, ignore the input
					if (InputKeyStateController.GetKeyState(Key) == NewKeyState)
					{
						return;
					}

					// Update input key state
					InputKeyStateController.SetKeyState(Key, NewKeyState);

					// Handle the input
					FUIInputActionValue Value{};
					// Determine value
					SetUIInputActionValue(Value, KeyMapping, FUIInputActionValue::ReleasedValue);

					// Call bound event on screen widget
					(UserObject->*Event)(Value);
				}
			);

			PlayerController->InputComponent->KeyBindings.Add(AnyKeyReleasedBinding);

			// Repeat bindings
			if (KeyMapping.bAcceptRepeatInputs)
			{
				FInputKeyBinding AnyKeyRepeatBinding(KeyMapping.Key, EInputEvent::IE_Repeat);
				AnyKeyRepeatBinding.bConsumeInput = KeyMapping.bConsumeInput;
				AnyKeyRepeatBinding.bExecuteWhenPaused = KeyMapping.bExecuteWhenPaused;
				AnyKeyRepeatBinding.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([this, UserObject, Event, KeyMapping](const FKey& Key)
					{
						// The mapped key was repeated
						// Handle the input
						FUIInputActionValue Value{};
						// Determine value
						SetUIInputActionValue(Value, KeyMapping, FUIInputActionValue::PressedValue);

						// Call bound event on screen widget
						(UserObject->*Event)(Value);
					}
				);

				PlayerController->InputComponent->KeyBindings.Add(AnyKeyRepeatBinding);
			}
		}
	}

private:
	void NativeOnInitialized() override;

	virtual void SetupUIInputActionEvents() {};

	void SetUIInputActionValue(FUIInputActionValue& Value, const FUIInputActionKeyMapping& Mapping, float Data);
};
