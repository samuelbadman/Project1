// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidgets/Project1UserWidgetBase.h"
#include "GameplayTagContainer.h"
#include "ScreenUserWidgetBase.generated.h"

class UUIInputAction;
struct FUIInputActionValue;

struct FUIInputActionEventBinding
{
	typedef void (UScreenUserWidgetBase::* UIInputActionEvent)(const FUIInputActionValue&);

	UScreenUserWidgetBase* UserObject{ nullptr };
	UIInputActionEvent Event{ nullptr };
};

/**
 *
 */
UCLASS()
class PROJECT1_API UScreenUserWidgetBase : public UProject1UserWidgetBase
{
	GENERATED_BODY()

private:
	TMap<TObjectPtr<UUIInputAction>, FUIInputActionEventBinding> UIInputActionEventBindings{};

public:
	void OnRawInput(const FKey& Key, EInputEvent InputEvent);

	FORCEINLINE const TMap<TObjectPtr<UUIInputAction>, FUIInputActionEventBinding>& GetUIInputActionEventBindings() const { return UIInputActionEventBindings; }

protected:
	template <typename T>
	void BindUIInputActionEvent(TObjectPtr<UUIInputAction> UIInputAction, UScreenUserWidgetBase* UserObject, void (T::* Event)(const FUIInputActionValue&))
	{
		UIInputActionEventBindings.Add(UIInputAction,
			FUIInputActionEventBinding{ .UserObject = UserObject, .Event = static_cast<FUIInputActionEventBinding::UIInputActionEvent>(Event) });
	}

private:
	void NativeOnInitialized() override;

	virtual void SetupUIInputActionEvents() {};
};
