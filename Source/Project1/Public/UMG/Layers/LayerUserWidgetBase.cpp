// Fill out your copyright notice in the Description page of Project Settings.


#include "LayerUserWidgetBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstances/Project1GameInstanceBase.h"
#include "UMG/Screens/ScreenUserWidgetBase.h"
#include "Components/PanelWidget.h"
#include "Objects/ScreenLoadPayloads/ScreenWidgetLoadPayloadBase.h"

static constexpr ESlateVisibility ScreenShownSlateVisibility{ ESlateVisibility::SelfHitTestInvisible };
static constexpr ESlateVisibility ScreenHiddenSlateVisibility{ ESlateVisibility::Collapsed };

void ULayerUserWidgetBase::PushContent(const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass, const TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayloadObject, bool Async)
{
	if (UKismetSystemLibrary::IsValidSoftClassReference(WidgetClass))
	{
		FStreamableManager& StreamableManager{ CastChecked<UProject1GameInstanceBase>(UGameplayStatics::GetGameInstance(this))->GetStreamableManager() };

		if (Async)
		{
			const TObjectPtr<UWidgetLayerClassASyncLoadHandle> NewHandle{ NewObject<UWidgetLayerClassASyncLoadHandle>() };

			PushedContentClassASyncLoadHandles.Add(NewHandle);

			NewHandle->WidgetLayer = this;
			NewHandle->LoadPayload = LoadPayloadObject;
			NewHandle->StreamableHandle = StreamableManager.RequestAsyncLoad(
				WidgetClass.ToSoftObjectPath(),
				FStreamableDelegate::CreateUObject(NewHandle, &UWidgetLayerClassASyncLoadHandle::OnLoadedClass)
			);
		}
		else
		{
			// Load payload is used immediately so no reference is kept to load payload object and it can be garbage collected on the next run of the garbage collector
			ActionPushedContent(StreamableManager.RequestSyncLoad(WidgetClass.ToSoftObjectPath())->GetLoadedAsset<UClass>(), LoadPayloadObject);
		}
	}
}

void ULayerUserWidgetBase::PopContent()
{
	if (IsEmpty())
	{
		return;
	}

	// Set top to the current widget on top of the stack
	TObjectPtr<UScreenUserWidgetBase> Top{ Peek() };
	Top->SetOwningLayer({});
	Top->RemoveFromParent();
	WidgetStack.RemoveAt(WidgetStack.Num() - 1);

	const TObjectPtr<UPanelWidget> PanelWidget{ GetPanelWidget() };
	PanelWidget->ClearChildren();

	Top->NativeOnPoppedFromLayerStack();
	Top->OnPoppedFromLayerStack();

	ContentPoppedFromLayer.Broadcast(Top);

	// Update top to the new widget that is currently on top of the stack. There may not be one so this can be null
	Top = Peek();
	if (IsValid(Top))
	{
		PanelWidget->AddChild(Top);
		Top->SetVisibility(ScreenShownSlateVisibility);
	}
}

TObjectPtr<UScreenUserWidgetBase> ULayerUserWidgetBase::Peek() const
{
	if (IsEmpty())
	{
		return nullptr;
	}

	return WidgetStack.Last();
}

void ULayerUserWidgetBase::CollapseTop()
{
	const TObjectPtr<UScreenUserWidgetBase> Top{ Peek() };
	if (IsValid(Top))
	{
		Top->SetVisibility(ScreenHiddenSlateVisibility);
		Top->NativeOnCollapsed();
		Top->OnCollapsed();
	}
}

void ULayerUserWidgetBase::ShowTop()
{
	const TObjectPtr<UScreenUserWidgetBase> Top{ Peek() };
	if (IsValid(Top))
	{
		Top->SetVisibility(ScreenShownSlateVisibility);
		Top->NativeOnShown();
		Top->OnShown();
	}
}

bool ULayerUserWidgetBase::IsEmpty() const
{
	return WidgetStack.IsEmpty();
}

bool ULayerUserWidgetBase::IsContentTop(TObjectPtr<UScreenUserWidgetBase> Content) const
{
	return (Peek() == Content);
}

bool ULayerUserWidgetBase::ShouldBlockLowerPriorityLayerInput() const
{
	const TObjectPtr<UScreenUserWidgetBase> Top{ Peek() };

	if (!IsValid(Top))
	{
		return false;
	}

	return Top->bBlockLowerPriorityLayerInput;
}

void ULayerUserWidgetBase::OnASyncLoadedPushedContentWidgetClass(TObjectPtr<UWidgetLayerClassASyncLoadHandle> Handle)
{
	PushedContentClassASyncLoadHandles.Remove(Handle);
	ActionPushedContent(Handle->StreamableHandle->GetLoadedAsset<UClass>(), Handle->LoadPayload);
}

void ULayerUserWidgetBase::ActionPushedContent(TObjectPtr<UClass> Class, TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayload)
{
	const TObjectPtr<UScreenUserWidgetBase> PushedWidget{ CreateWidget<UScreenUserWidgetBase>(GetOwningPlayer(),Class) };

	CollapseTop();

	const TObjectPtr<UPanelWidget> PanelWidget{ GetPanelWidget() };
	PanelWidget->ClearChildren();

	WidgetStack.Add(PushedWidget);
	PanelWidget->AddChild(PushedWidget);

	PushedWidget->SetOwningLayer(this);

	if (IsValid(LoadPayload))
	{
		PushedWidget->NativeConsumeLoadPayload(LoadPayload);
		PushedWidget->ConsumeLoadPayload(LoadPayload);
	}

	// Show the screen widget without calling the screen's on shown events. This is so that on pushed screen events can behave similarly to a begin play event
	const TObjectPtr<UScreenUserWidgetBase> Top{ Peek() };
	if (IsValid(Top))
	{
		Top->SetVisibility(ScreenShownSlateVisibility);
	}

	PushedWidget->NativeOnPushedToLayerStack();
	PushedWidget->OnPushedToLayerStack();
	ContentPushedToLayer.Broadcast(PushedWidget);
}
