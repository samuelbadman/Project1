// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1HUDBase.h"
#include "UMG/PrimaryLayouts/PrimaryLayoutUserWidgetBase.h"
#include "UMG/Layers/LayerUserWidgetBase.h"
#include "Objects/ScreenLoadPayloads/ConfirmModalScreenLoadPayload.h"
#include "Objects/ScreenLoadPayloads/DynamicModalScreenLoadPayload.h"

void AProject1HUDBase::PushContentToPrimaryLayoutWidgetLayer(
	const FGameplayTag& LayerName,
	const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass,
	UScreenWidgetLoadPayloadBase* const LoadPayloadObject,
	bool Async
)
{
	PrimaryLayoutWidget->PushContentToLayer(LayerName, WidgetClass, LoadPayloadObject, Async);
}

void AProject1HUDBase::PopContentFromPrimaryLayoutWidgetLayer(const FGameplayTag& LayerName)
{
	PrimaryLayoutWidget->PopContentFromLayer(LayerName);
}

ULayerUserWidgetBase* AProject1HUDBase::GetRegisteredPrimaryLayoutWidgetLayer(const FGameplayTag& LayerName) const
{
	return PrimaryLayoutWidget->GetRegisteredLayer(LayerName);
}

UScreenUserWidgetBase* AProject1HUDBase::PeekPrimaryLayoutWidgetLayer(const FGameplayTag& LayerName) const
{
	return PrimaryLayoutWidget->GetRegisteredLayer(LayerName)->Peek();
}

bool AProject1HUDBase::DoesPrimaryLayoutWidgetLayerBlockContentInput(const int32 ContentLayerPriority) const
{
	return PrimaryLayoutWidget->DoesLayerBlockContentInput(ContentLayerPriority);
}

bool AProject1HUDBase::IsPrimaryLayoutWidgetLayerEmpty(const FGameplayTag& LayerName) const
{
	return PrimaryLayoutWidget->GetRegisteredLayer(LayerName)->IsEmpty();
}

void AProject1HUDBase::PushConfirmModalToWidgetLayer(
	const FGameplayTag& LayerName, 
	const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass,
	const FText ModalPromptText,
	const FText Option1Text,
	const FText Option2Text,
	const FConfirmModalOptionSelectedDelegate& Option1SelectedDelegate,
	const FConfirmModalOptionSelectedDelegate& Option2SelectedDelegate,
	bool Async
)
{
	const TObjectPtr<UConfirmModalScreenLoadPayload> ModalLoadPayload{ NewObject<UConfirmModalScreenLoadPayload>() };
	ModalLoadPayload->ModalPromptText = ModalPromptText;
	ModalLoadPayload->Option1Text = Option1Text;
	ModalLoadPayload->Option2Text = Option2Text;
	ModalLoadPayload->Option1SelectedDelegate = Option1SelectedDelegate;
	ModalLoadPayload->Option2SelectedDelegate = Option2SelectedDelegate;

	PushContentToPrimaryLayoutWidgetLayer(LayerName, WidgetClass, ModalLoadPayload, Async);
}

void AProject1HUDBase::PushDynamicModalToWidgetLayer(
	const FGameplayTag& LayerName,
	const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass,
	const FText ModalPromptText,
	const TArray<FDynamicModalOptionData>& Options,
	bool Async
	)
{
	const TObjectPtr<UDynamicModalScreenLoadPayload> ModalLoadPayload{ NewObject<UDynamicModalScreenLoadPayload>() };
	ModalLoadPayload->ModalPromptText = ModalPromptText;
	ModalLoadPayload->Options = Options;

	PushContentToPrimaryLayoutWidgetLayer(LayerName, WidgetClass, ModalLoadPayload, Async);
}

void AProject1HUDBase::CreatePrimaryLayoutWidget()
{
	// Create primary layout widget, cache it and add it to the viewport
	PrimaryLayoutWidget = CreateWidget<UPrimaryLayoutUserWidgetBase>(GetOwningPlayerController(), PrimaryLayoutWidgetClass);
#if WITH_EDITOR
	if (!IsValid(PrimaryLayoutWidget))
	{
		UE_LOG(LogTemp, Error, TEXT("PrimaryLayoutWidget failed to create. Is a class set in the HUD blueprint?"));
		return;
	}
#endif
	PrimaryLayoutWidget->AddToViewport();
}
