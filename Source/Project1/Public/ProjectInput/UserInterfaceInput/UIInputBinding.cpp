#include "UIInputBinding.h"
#include "ProjectInput/InputKeyStateController.h"
#include "ProjectInput/UserInterfaceInput/UIInputAction.h"
#include "ProjectInput/UserInterfaceInput/UIInputActionKeyMapping.h"

void FUIInputBinding::OnBoundUIInputActionInput(UInputKeyStateController& InputKeyStateController, EInputEvent InputEvent, const FUIInputActionKeyMapping& KeyMapping)
{
	// Get new key state for the input key
	const EInputKeyState NewKeyState{ InputKeyStateController.GetInputKeyStateFromInputEvent(InputEvent) };

	// If the input was pressed or released and the key is already in the new key state, ignore the input. This prevents held keys when opening a new level from triggering inaccurate 
	// pressed events
	if ((InputEvent == IE_Pressed) ||
		(InputEvent == IE_Released))
	{
		if (InputKeyStateController.GetKeyState(KeyMapping.Key) == NewKeyState)
		{
			return;
		}
	}

	// Update input key state
	InputKeyStateController.SetKeyState(KeyMapping.Key, NewKeyState);

	// Handle the input
	// Determine input value
	// Get input value type from the bound input action
	switch (InputAction->GetInputValueType())
	{
	case EUIInputValueType::Float1D:
		switch (InputEvent)
		{
		case EInputEvent::IE_Pressed: InputValue.Default1DAxis = FUIInputActionValue::PressedValue * KeyMapping.InputValueScale; break;
		case EInputEvent::IE_Released: InputValue.Default1DAxis = FUIInputActionValue::ReleasedValue * KeyMapping.InputValueScale; break;
		case EInputEvent::IE_Repeat: InputValue.Default1DAxis = FUIInputActionValue::PressedValue * KeyMapping.InputValueScale; break;
		default: break;
		}
		break;

	case EUIInputValueType::FVector2D:
		switch (KeyMapping.InputAxisSwizzle)
		{
		case EUIInputAxisSwizzle::XY:
			switch (InputEvent)
			{
			case EInputEvent::IE_Pressed: InputValue.Default1DAxis = FUIInputActionValue::PressedValue * KeyMapping.InputValueScale; break;
			case EInputEvent::IE_Released: InputValue.Default1DAxis = FUIInputActionValue::ReleasedValue * KeyMapping.InputValueScale; break;
			case EInputEvent::IE_Repeat: InputValue.Default1DAxis = FUIInputActionValue::PressedValue * KeyMapping.InputValueScale; break;
			default: break;
			}
			break;

		case EUIInputAxisSwizzle::YX:
			switch (InputEvent)
			{
			case EInputEvent::IE_Pressed: InputValue.Axis2D = FUIInputActionValue::PressedValue * KeyMapping.InputValueScale; break;
			case EInputEvent::IE_Released: InputValue.Axis2D = FUIInputActionValue::ReleasedValue * KeyMapping.InputValueScale; break;
			case EInputEvent::IE_Repeat: InputValue.Axis2D = FUIInputActionValue::PressedValue * KeyMapping.InputValueScale; break;
			default: break;
			}
			break;
		}
	}

	// Call bound event with value
	Event.ExecuteIfBound(InputValue);

	// Reset the value for the next input
	InputValue.Reset();
}