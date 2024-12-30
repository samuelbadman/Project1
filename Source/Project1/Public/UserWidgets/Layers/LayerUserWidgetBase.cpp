// Fill out your copyright notice in the Description page of Project Settings.


#include "LayerUserWidgetBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameInstances/Project1GameInstanceBase.h"
#include "UserWidgets/Screens/ScreenUserWidgetBase.h"
#include "Components/PanelWidget.h"

void ULayerUserWidgetBase::PushContent(const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass)
{
	if (UKismetSystemLibrary::IsValidSoftClassReference(WidgetClass))
	{
		const TObjectPtr<UWidgetLayerClassASyncLoadHandle> NewHandle{ NewObject<UWidgetLayerClassASyncLoadHandle>() };

		PushedContentClassASyncLoadHandles.Add(NewHandle);

		NewHandle->WidgetLayer = this;
		NewHandle->StreamableHandle = Cast<UProject1GameInstanceBase>(UGameplayStatics::GetGameInstance(this))->GetStreamableManager().RequestAsyncLoad(
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

	TObjectPtr<UScreenUserWidgetBase> Top{ Peek() };
	Top->RemoveFromParent();
	WidgetStack.RemoveAt(WidgetStack.Num() - 1);

	const TObjectPtr<UPanelWidget> PanelWidget{ GetPanelWidget() };
	PanelWidget->ClearChildren();

	OnContentPoppedFromLayerDelegate.Broadcast(Top);

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
	}
}

void ULayerUserWidgetBase::ShowTop()
{
	const TObjectPtr<UScreenUserWidgetBase> Top{ Peek()};
	if (IsValid(Top))
	{
		Top->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
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

	ShowTop();

	PushedContentClassASyncLoadHandles.Remove(Handle);

	OnContentPushedToLayerDelegate.Broadcast(PushedWidget);
}
