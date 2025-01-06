#include "UIInputBinding.h"
#include "ProjectInput/InputKeyStateController.h"
#include "ProjectInput/UserInterfaceInput/UIInputAction.h"
#include "ProjectInput/UserInterfaceInput/UIInputActionKeyMapping.h"
#include "UIInputActionTriggerBase.h"

void FUIInputBinding::OnBoundUIInputActionInput(const FKey& InputKey, EInputEvent InputEvent)
{
	for (const auto& KeyPropertiesPair : KeyMapping.Keys)
	{
		// Ignore any key as this is a special key that always be handled as the value of InputKey will never be 'AnyKey'
		if (KeyPropertiesPair.Key != EKeys::AnyKey)
		{
			// Check if the input key matches this key
			if (InputKey != KeyPropertiesPair.Key)
			{
				continue;
			}
		}

		// Ignore input from exluded keys
		if (KeyPropertiesPair.Value.bExcludeInputKeys)
		{
			if (KeyPropertiesPair.Value.ExcludedKeys.Contains(InputKey))
			{
				continue;
			}
		}

		// Handle the input
		// Get raw input value
		static constexpr float DefaultRawInputValue{ 0.0f };
		float RawInputValue{ DefaultRawInputValue };
		switch (InputEvent)
		{
		case EInputEvent::IE_Pressed: RawInputValue = FUIInputActionValue::PressedValue; break;
		case EInputEvent::IE_Released: RawInputValue = FUIInputActionValue::ReleasedValue; break;
		case EInputEvent::IE_Repeat: RawInputValue = FUIInputActionValue::PressedValue; break;
		default: break;
		}

		// Build input value
		switch (KeyPropertiesPair.Value.InputAxisSwizzle)
		{
		case EUIInputAxisSwizzle::XY: InputValue.Default1DAxis = RawInputValue * KeyPropertiesPair.Value.InputValueScale; break;
		case EUIInputAxisSwizzle::YX: InputValue.Axis2D = RawInputValue * KeyPropertiesPair.Value.InputValueScale; break;
		default: break;
		}

		// Call bound event with value each time it is triggered by a trigger rule on the input action
		const auto& Triggers{ InputAction->GetTriggers() };
		// If no triggers are set call bound event for every input
		if (Triggers.IsEmpty())
		{
			Event.ExecuteIfBound(InputValue);
		}
		else
		{
			for (const auto Trigger : Triggers)
			{
				// Determine if the input action has been triggered
				// Check if the trigger is valid. This allows "none" to be set in the input action to reject all input
				if (IsValid(Trigger))
				{
					if (Trigger->Evaluate(RawInputValue, InputEvent))
					{
						Event.ExecuteIfBound(InputValue);
					}
				}
			}
		}

		// Reset the value for the next input
		InputValue.Reset();
	}
}