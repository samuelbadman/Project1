// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimaryLayoutUserWidgetBase.h"
#include "UserWidgets/Layers/LayerUserWidgetBase.h"
#include "UserWidgets/Screens/ScreenUserWidgetBase.h"
#include "ProjectInput/UserInterfaceInput/UIInputActionMapping.h"
#include "ProjectInput/UserInterfaceInput/UIInputActionValue.h"

bool UPrimaryLayoutUserWidgetBase::RegisterLayer(const FGameplayTag& LayerName, ULayerUserWidgetBase* LayerWidget)
{
	if (!IsValid(LayerWidget))
	{
		return false;
	}

	if (Layers.Contains(LayerName))
	{
		return false;
	}

	Layers.Add(LayerName, LayerWidget);
	return true;
}

bool UPrimaryLayoutUserWidgetBase::UnregisterLayer(const FGameplayTag& LayerName)
{
	TObjectPtr<ULayerUserWidgetBase>* const pLayer{ Layers.Find(LayerName) };

	if (pLayer)
	{
		pLayer->Get()->RemoveFromParent();
	}

	return (Layers.Remove(LayerName) > 0);
}

void UPrimaryLayoutUserWidgetBase::PushContentToLayer(const FGameplayTag& LayerName, const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass)
{
	TObjectPtr<ULayerUserWidgetBase>* const pLayer{ Layers.Find(LayerName) };

	if (pLayer)
	{
		pLayer->Get()->PushContent(WidgetClass);
	}
}

void UPrimaryLayoutUserWidgetBase::PopContentFromLayer(const FGameplayTag& LayerName)
{
	TObjectPtr<ULayerUserWidgetBase>* const pLayer{ Layers.Find(LayerName) };

	if (pLayer)
	{
		pLayer->Get()->PopContent();
	}
}

ULayerUserWidgetBase* UPrimaryLayoutUserWidgetBase::GetRegisteredLayer(const FGameplayTag& LayerName)
{
	TObjectPtr<ULayerUserWidgetBase>* const pLayer{ Layers.Find(LayerName) };

	if (!pLayer)
	{
		return nullptr;
	}

	return pLayer->Get();
}

void UPrimaryLayoutUserWidgetBase::SetActiveInputLayer(const FGameplayTag& LayerName)
{
	ActiveInputLayerName = LayerName;
}

void UPrimaryLayoutUserWidgetBase::ReceiveRawInput(const FKey& Key, EInputEvent InputEvent)
{
	TObjectPtr<ULayerUserWidgetBase>* const pActiveInputLayer{ Layers.Find(ActiveInputLayerName) };
	if (pActiveInputLayer)
	{
		const TObjectPtr<UScreenUserWidgetBase> TopScreen{ (*pActiveInputLayer)->Peek() };

		if (IsValid(TopScreen))
		{
			// Handle raw input
			if (bReceiveRawInput)
			{
				TopScreen->OnRawInput(Key, InputEvent);

				if (bRawInputConsumesUIInput)
				{
					return;
				}
			}

			// Handle UI input
			// Is the input key mapped to an input action?
			const auto& ActionMapping{ UIInputActionMapping->GetActionMapping() };

			// For each mapping value mapped to an UI input action in the action mapping
			for (const auto& MappingValue : ActionMapping)
			{
				// The mapping value contains a mapping that contains a list of keys that are mapped to the UI input action
				for (const auto& Mapping : MappingValue.Value.Mapping)
				{
					// Reject the input if the raw input is a repeat input and the mapping does not accept repeat inputs
					if ((!Mapping.bAcceptRepeatInputs) &&
						(InputEvent == EInputEvent::IE_Repeat))
					{
						continue;
					}

					// If the raw input key matches a mapped key, call the input
					if (Mapping.Key == Key)
					{
						// Pass the input to the top screen of the active input layer to be handled there
						TObjectPtr<ULayerUserWidgetBase>* pLayer{ Layers.Find(ActiveInputLayerName) };
						if (pLayer)
						{
							const TObjectPtr<UScreenUserWidgetBase> Top{ (*pLayer)->Peek() };
							if (IsValid(Top))
							{
								// If the screen widget has subscribed to this input action
								const FUIInputActionEventBinding* pEventBinding{ Top->GetUIInputActionEventBindings().Find(MappingValue.Key) };
								if (pEventBinding)
								{
									// Validate top screen widget is the screen that has bound the event
									if (pEventBinding->UserObject == Top)
									{
										FUIInputActionValue Value{};
										// Determine value from pressed/released input event. Pressed = 1, released = 0
										Value.Value = (((InputEvent == EInputEvent::IE_Pressed) || (InputEvent == EInputEvent::IE_Repeat)) ? 1.0f : 0.0f) * Mapping.ValueScale;

										// Call bound event on screen widget
										(Top->*pEventBinding->Event)(Value);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
