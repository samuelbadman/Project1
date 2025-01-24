// Fill out your copyright notice in the Description page of Project Settings.


#include "LayerUserWidgetBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstances/Project1GameInstanceBase.h"
#include "UserWidgets/Screens/Widgets/ScreenUserWidgetBase.h"
#include "Components/PanelWidget.h"
#include "UserWidgets/Screens/ScreenLoadPayloads/ScreenWidgetLoadPayloadBase.h"

void ULayerUserWidgetBase::SetLayerName(const FGameplayTag& Name)
{
	LayerName = Name;
}

void ULayerUserWidgetBase::PushContent(const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass, const TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayloadObject)
{
	if (UKismetSystemLibrary::IsValidSoftClassReference(WidgetClass))
	{
		FStreamableManager& StreamableManager{ CastChecked<UProject1GameInstanceBase>(UGameplayStatics::GetGameInstance(this))->GetStreamableManager() };
		const TObjectPtr<UWidgetLayerClassASyncLoadHandle> NewHandle{ NewObject<UWidgetLayerClassASyncLoadHandle>() };

		PushedContentClassASyncLoadHandles.Add(NewHandle);

		NewHandle->WidgetLayer = this;
		NewHandle->LoadPayload = LoadPayloadObject; 
		NewHandle->StreamableHandle = StreamableManager.RequestAsyncLoad(
			WidgetClass.ToSoftObjectPath(),
			FStreamableDelegate::CreateUObject(NewHandle, &UWidgetLayerClassASyncLoadHandle::OnLoadedClass)
		);
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
	Top->SetOwningLayerName({});
	Top->RemoveFromParent();
	WidgetStack.RemoveAt(WidgetStack.Num() - 1);

	const TObjectPtr<UPanelWidget> PanelWidget{ GetPanelWidget() };
	PanelWidget->ClearChildren();

	Top->NativeOnPoppedFromLayerStack();
	Top->OnPoppedFromLayerStack();

	OnContentPoppedFromLayerDelegate.Broadcast(Top);

	// Update top to the new widget that is currently on top of the stack. There may not be one so this can be null
	Top = Peek();
	if (IsValid(Top))
	{
		PanelWidget->AddChild(Top);
		Top->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
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
		Top->SetVisibility(ESlateVisibility::Collapsed);
		Top->NativeOnCollapsed();
		Top->OnCollapsed();
	}
}

void ULayerUserWidgetBase::ShowTop()
{
	const TObjectPtr<UScreenUserWidgetBase> Top{ Peek()};
	if (IsValid(Top))
	{
		Top->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		Top->NativeOnShown();
		Top->OnShown();
	}
}

bool ULayerUserWidgetBase::IsEmpty() const
{
	return WidgetStack.IsEmpty();
}

void ULayerUserWidgetBase::OnLoadedPushedContentWidgetClass(TObjectPtr<UWidgetLayerClassASyncLoadHandle> Handle)
{
	const TObjectPtr<UScreenUserWidgetBase> PushedWidget{ CreateWidget<UScreenUserWidgetBase>(GetOwningPlayer(), Handle->StreamableHandle->GetLoadedAsset<UClass>()) };

	CollapseTop();

	const TObjectPtr<UPanelWidget> PanelWidget{ GetPanelWidget() };
	PanelWidget->ClearChildren();

	WidgetStack.Add(PushedWidget);
	PanelWidget->AddChild(PushedWidget);

	PushedWidget->SetOwningLayerName(LayerName);

	if (IsValid(Handle->LoadPayload))
	{
		PushedWidget->NativeConsumeLoadPayload(Handle->LoadPayload);
		PushedWidget->ConsumeLoadPayload(Handle->LoadPayload);
	}

	PushedContentClassASyncLoadHandles.Remove(Handle);

	// Show the screen widget without calling the screen's on shown events. This is so that on pushed screen events can behave similarly to a begin play event
	const TObjectPtr<UScreenUserWidgetBase> Top{ Peek() };
	if (IsValid(Top))
	{
		Top->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	PushedWidget->NativeOnPushedToLayerStack();
	PushedWidget->OnPushedToLayerStack();
	OnContentPushedToLayerDelegate.Broadcast(PushedWidget);
}
