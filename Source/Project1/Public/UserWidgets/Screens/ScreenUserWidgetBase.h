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

		// Get the UI input action mapping. This is where inputs can be disabled by implementing a system that uses multiple input mapping assets with priorities similiar to enhanced input
		const TObjectPtr<const UUIInputActionMapping> InputActionMapping{ HUD->GetUIInputActionMapping() };

		const auto& ActionMapping{ InputActionMapping->GetActionMapping() };
		const FUIInputActionMappingValue* pActionMappingValue{ ActionMapping.Find(UIInputAction) };
		for (const auto& KeyMapping : pActionMappingValue->Mapping)
		{
			FInputKeyBinding AnyKeyPressedBinding(KeyMapping.Key, EInputEvent::IE_Pressed);
			AnyKeyPressedBinding.bConsumeInput = KeyMapping.bConsumeInput;
			AnyKeyPressedBinding.bExecuteWhenPaused = KeyMapping.bExecuteWhenPaused;
			AnyKeyPressedBinding.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([UserObject, Event, KeyMapping](const FKey& Key)
				{
					// The mapped key was pressed
					FUIInputActionValue Value{};
					// Determine value from pressed/released input event. Pressed = 1, released = 0
					Value.Value = 1.0f * KeyMapping.ValueScale;

					// Call bound event on screen widget
					(UserObject->*Event)(Value);
				}
			);

			FInputKeyBinding AnyKeyReleasedBinding(KeyMapping.Key, EInputEvent::IE_Released);
			AnyKeyReleasedBinding.bConsumeInput = KeyMapping.bConsumeInput;
			AnyKeyReleasedBinding.bExecuteWhenPaused = KeyMapping.bExecuteWhenPaused;
			AnyKeyReleasedBinding.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([UserObject, Event, KeyMapping](const FKey& Key)
				{
					// The mapped key was released
					FUIInputActionValue Value{};
					// Determine value from pressed/released input event. Pressed = 1, released = 0
					Value.Value = 0.0f;

					// Call bound event on screen widget
					(UserObject->*Event)(Value);
				}
			);

			PlayerController->InputComponent->KeyBindings.Add(AnyKeyPressedBinding);
			PlayerController->InputComponent->KeyBindings.Add(AnyKeyReleasedBinding);

			if (KeyMapping.bAcceptRepeatInputs)
			{
				FInputKeyBinding AnyKeyRepeatBinding(KeyMapping.Key, EInputEvent::IE_Repeat);
				AnyKeyRepeatBinding.bConsumeInput = KeyMapping.bConsumeInput;
				AnyKeyRepeatBinding.bExecuteWhenPaused = KeyMapping.bExecuteWhenPaused;
				AnyKeyRepeatBinding.KeyDelegate.GetDelegateWithKeyForManualSet().BindLambda([UserObject, Event, KeyMapping](const FKey& Key)
					{
						// The mapped key was repeated
						FUIInputActionValue Value{};
						// Determine value from pressed/released input event. Pressed = 1, released = 0
						Value.Value = 1.0f * KeyMapping.ValueScale;

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
};
