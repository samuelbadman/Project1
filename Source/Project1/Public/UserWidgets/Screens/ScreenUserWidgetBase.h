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
	TObjectPtr<AProject1PlayerControllerBase> Project1PlayerController{ nullptr };
	TObjectPtr<AProject1HUDBase> Project1HUD{ nullptr };
	TObjectPtr<UProject1GameInstanceBase> Project1GameInstance{ nullptr };

	// The name of the UI widget layer that owns this screen. The name of the widget layer the screen widget was pushed to
	FGameplayTag OwningLayerName{};

	// Inputs bound to by this screen widget
	TArray<FUIInputBinding> InputBindings{};

public:
	void SetOwningLayerName(const FGameplayTag& LayerName);

	UFUNCTION(BlueprintImplementableEvent)
	void OnPushedToLayerStack();

	UFUNCTION(BlueprintImplementableEvent)
	void OnShown();

	UFUNCTION(BlueprintImplementableEvent)
	void OnCollapsed();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPoppedFromLayerStack();

	// Called when the widget is pushed to a widget layer stack
	virtual void NativeOnPushedToLayerStack() {};
	// Called when the widget is manually shown on top of a widget layer stack by calling ShowTop on the layer
	virtual void NativeOnShown() {};
	// Called when the widget is manually collapsed on top of a widget layer stack by calling CollapseTop on the layer
	virtual void NativeOnCollapsed() {};
	// Called when widget is popped from a widget layer stack
	virtual void NativeOnPoppedFromLayerStack() {};

	void ProcessInput(const FKey& Key, const EInputEvent Event);

protected:
	void NativeOnInitialized() override;

	FORCEINLINE const FGameplayTag& GetOwningLayerName() const { return OwningLayerName; }

	template <typename T>
	void BindUIInputActionEvent(TObjectPtr<UUIInputAction> UIInputAction, T* UserObject, void (T::* Event)(const FUIInputActionValue&))
	{
		// Do not bind if UI input action is invalid
		if (!IsValid(UIInputAction))
		{
			return;
		}

		// Get keys mapped to input action from input action mapping. The mapping is stored in the primary layout widget that exists in the HUD
		// Get the UI input action mapping. This is where inputs can be disabled by implementing a system that uses multiple input mapping assets with
		// priorities similiar to Unreal's enhanced input system
		const TObjectPtr<const UUIInputActionMapping> InputActionMapping{ Project1HUD->GetUIInputActionMapping() };

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

		// Get action mapping value for input action being bound to. The action mapping value contains a list of mappings to the input action
		const FUIInputActionMappingValue* pActionMappingValue{ ActionMapping.Find(UIInputAction) };

		// Copy mappings to input binding struct
		InputBindings[BindingIndex].KeyMappings = pActionMappingValue->Mapping;
	}

private:
	virtual void SetupUIInputActionEvents() {};
};
