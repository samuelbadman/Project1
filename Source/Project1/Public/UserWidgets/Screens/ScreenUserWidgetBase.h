// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Project1UserWidgetBase.h"
#include "GameplayTagContainer.h"
#include "Kismet/GameplayStatics.h"
#include "HUDs/Project1HUDBase.h"
#include "PlayerControllers/Project1PlayerControllerBase.h"
#include "ProjectInput/UserInterfaceInput/UIInputAction.h"
#include "ProjectInput/UserInterfaceInput/UIInputActionMapping.h"
#include "ProjectInput/UserInterfaceInput/UIInputActionValue.h"
#include "GameInstances/Project1GameInstanceBase.h"
#include "ProjectInput/InputKeyStateController.h"
#include "ProjectInput/UserInterfaceInput/UIInputBinding.h"
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

private:
	TArray<FUIInputBinding> InputBindings{};

protected:
	template <typename T>
	void BindUIInputActionEvent(TObjectPtr<UUIInputAction> UIInputAction, T* UserObject, void (T::* Event)(const FUIInputActionValue&))
	{
		// Do not bind if UI input action is invalid
		if (!IsValid(UIInputAction))
		{
			return;
		}

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

		// Add new input binding
		const int32 BindingIndex{ InputBindings.Add(FUIInputBinding()) };
		InputBindings[BindingIndex].InputAction = UIInputAction;
		InputBindings[BindingIndex].Event.BindUObject(UserObject, Event);

		// Get action mapping from input action mapping. The action mapping contains the actual mapping of keys to UI input action
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
			AnyKeyPressedBinding.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([this, BindingIndex, GameInstance, KeyMapping](const FKey& Key)
				{
					InputBindings[BindingIndex].OnBoundUIInputActionInput(GameInstance->GetInputKeyStateController(), Key, EInputEvent::IE_Pressed, KeyMapping);
				}
			);

			PlayerController->InputComponent->KeyBindings.Add(AnyKeyPressedBinding);

			// Released binding
			FInputKeyBinding AnyKeyReleasedBinding(KeyMapping.Key, EInputEvent::IE_Released);
			AnyKeyReleasedBinding.bConsumeInput = KeyMapping.bConsumeInput;
			AnyKeyReleasedBinding.bExecuteWhenPaused = KeyMapping.bExecuteWhenPaused;
			AnyKeyReleasedBinding.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([this, BindingIndex, GameInstance, KeyMapping](const FKey& Key)
				{
					InputBindings[BindingIndex].OnBoundUIInputActionInput(GameInstance->GetInputKeyStateController(), Key, EInputEvent::IE_Released, KeyMapping);
				}
			);

			PlayerController->InputComponent->KeyBindings.Add(AnyKeyReleasedBinding);

			// Repeat bindings
			if (KeyMapping.bAcceptRepeatInputs)
			{
				FInputKeyBinding AnyKeyRepeatBinding(KeyMapping.Key, EInputEvent::IE_Repeat);
				AnyKeyRepeatBinding.bConsumeInput = KeyMapping.bConsumeInput;
				AnyKeyRepeatBinding.bExecuteWhenPaused = KeyMapping.bExecuteWhenPaused;
				AnyKeyRepeatBinding.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([this, BindingIndex, GameInstance, KeyMapping](const FKey& Key)
					{
						InputBindings[BindingIndex].OnBoundUIInputActionInput(GameInstance->GetInputKeyStateController(), Key, EInputEvent::IE_Repeat, KeyMapping);
					}
				);

				PlayerController->InputComponent->KeyBindings.Add(AnyKeyRepeatBinding);
			}
		}
	}

private:
	void NativeOnInitialized() override;

	virtual void SetupUIInputActionEvents() {};
};
