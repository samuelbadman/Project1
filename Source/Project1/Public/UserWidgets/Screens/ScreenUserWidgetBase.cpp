// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenUserWidgetBase.h"
#include "Kismet/GameplayStatics.h"

void UScreenUserWidgetBase::SetOwningLayerName(const FGameplayTag& LayerName)
{
	OwningLayerName = LayerName;
}

void UScreenUserWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Project1HUD = CastChecked<AProject1HUDBase>((UGameplayStatics::GetPlayerController(this, 0)->GetHUD()));

	SetupUIInputActionEvents();
}

void UScreenUserWidgetBase::ProcessInput(const FKey& Key, const EInputEvent Event)
{
	// For each input binding the screen widget has bound
	for (FUIInputBinding& InputBinding : InputBindings)
	{
		// For each key mapping in the binding
		for (const FUIInputActionKeyMapping& KeyMapping : InputBinding.KeyMappings)
		{
			// If the input key matches a key in the bound mapping
			if (KeyMapping.Key == EKeys::AnyKey) // Any key is its own key that does not equal other keys. If the mapped key is any key, call the binding regardless of input key
			{
				InputBinding.OnBoundUIInputActionInput(Key, Event, KeyMapping);
			}
			else if (Key == KeyMapping.Key)
			{
				InputBinding.OnBoundUIInputActionInput(Key, Event, KeyMapping);
			}
		}
	}
}
