// Fill out your copyright notice in the Description page of Project Settings.


#include "LayerUserWidgetBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameInstances/Project1GameInstanceBase.h"
#include "UserWidgets/Screens/ScreenUserWidgetBase.h"
#include "Components/PanelWidget.h"

void ULayerUserWidgetBase::SetLayerName(const FGameplayTag& Name)
{
	LayerName = Name;
}

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
	PushedWidget->NativeOnPushedToLayerStack();
	PushedWidget->OnPushedToLayerStack();

	ShowTop();

	PushedContentClassASyncLoadHandles.Remove(Handle);

	OnContentPushedToLayerDelegate.Broadcast(PushedWidget);
}

void ULayerUserWidgetBase::ReceiveOnMouseMoved(const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta)
{
	const TObjectPtr<UScreenUserWidgetBase> Top{ Peek() };
	if (IsValid(Top))
	{
		Top->NativeOnMouseMoved(NewMousePosition, OldMousePosition, MouseMoveDelta);
		Top->OnMouseMoved(NewMousePosition, OldMousePosition, MouseMoveDelta);
	}
}

void ULayerUserWidgetBase::ReceiveOnLeftClickTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<UScreenUserWidgetBase> Top{ Peek() };
	if (IsValid(Top))
	{
		Top->NativeOnLeftClickTriggered(Value);
		Top->OnLeftClickTriggered(Value);
	}
}

void ULayerUserWidgetBase::ReceiveOnMiddleClickTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<UScreenUserWidgetBase> Top{ Peek() };
	if (IsValid(Top))
	{
		Top->NativeOnMiddleClickTriggered(Value);
		Top->OnMiddleClickTriggered(Value);
	}
}

void ULayerUserWidgetBase::ReceiveOnRightClickTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<UScreenUserWidgetBase> Top{ Peek() };
	if (IsValid(Top))
	{
		Top->NativeOnRightClickTriggered(Value);
		Top->OnRightClickTriggered(Value);
	}
}

void ULayerUserWidgetBase::ReceiveOnMouseWheelTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<UScreenUserWidgetBase> Top{ Peek() };
	if (IsValid(Top))
	{
		Top->NativeOnMouseWheelTriggered(Value);
		Top->OnMouseWheelTriggered(Value);
	}
}

void ULayerUserWidgetBase::ReceiveOnNavigateTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<UScreenUserWidgetBase> Top{ Peek() };
	if (IsValid(Top))
	{
		Top->NativeOnNavigateTriggered(Value);
		Top->OnNavigateTriggered(Value);
	}
}

void ULayerUserWidgetBase::ReceiveOnConfirmTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<UScreenUserWidgetBase> Top{ Peek() };
	if (IsValid(Top))
	{
		Top->NativeOnConfirmTriggered(Value);
		Top->OnConfirmTriggered(Value);
	}
}

void ULayerUserWidgetBase::ReceiveOnCancelTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<UScreenUserWidgetBase> Top{ Peek() };
	if (IsValid(Top))
	{
		Top->NativeOnCancelTriggered(Value);
		Top->OnCancelTriggered(Value);
	}
}

void ULayerUserWidgetBase::ReceiveOnTabTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<UScreenUserWidgetBase> Top{ Peek() };
	if (IsValid(Top))
	{
		Top->NativeOnTabTriggered(Value);
		Top->OnTabTriggered(Value);
	}
}

void ULayerUserWidgetBase::ReceiveOnAnyInputTriggered(const FInputActionValue& Value)
{
	const TObjectPtr<UScreenUserWidgetBase> Top{ Peek() };
	if (IsValid(Top))
	{
		Top->NativeOnAnyInputTriggered(Value);
		Top->OnAnyInputTriggered(Value);
	}
}
