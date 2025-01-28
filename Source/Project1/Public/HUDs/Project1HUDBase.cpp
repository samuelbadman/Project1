// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1HUDBase.h"
#include "UMG/PrimaryLayouts/PrimaryLayoutUserWidgetBase.h"
#include "UMG/Screens/ScreenLoadPayloads/ConfirmModalScreenLoadPayload.h"

void AProject1HUDBase::PushContentToPrimaryLayoutWidgetLayer(
	const FGameplayTag& LayerName,
	const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass,
	UScreenWidgetLoadPayloadBase* const LoadPayloadObject
)
{
	PrimaryLayoutWidget->PushContentToLayer(LayerName, WidgetClass, LoadPayloadObject);
}

void AProject1HUDBase::PopContentFromPrimaryLayoutWidgetLayer(const FGameplayTag& LayerName)
{
	PrimaryLayoutWidget->PopContentFromLayer(LayerName);
}

TObjectPtr<ULayerUserWidgetBase> AProject1HUDBase::GetRegisteredPrimaryLayoutWidgetLayer(const FGameplayTag& LayerName) const
{
	return PrimaryLayoutWidget->GetRegisteredLayer(LayerName);
}

bool AProject1HUDBase::DoesPrimaryLayoutWidgetLayerBlockContentInput(const int32 ContentLayerPriority) const
{
	return PrimaryLayoutWidget->DoesLayerBlockContentInput(ContentLayerPriority);
}

void AProject1HUDBase::PushConfirmModalToWidgetLayer(
	const FGameplayTag& LayerName, 
	const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass,
	const FText ModalPromptText,
	const FText Option1Text,
	const FText Option2Text
)
{
	const TObjectPtr<UConfirmModalScreenLoadPayload> ModalLoadPayload{ NewObject<UConfirmModalScreenLoadPayload>() };
	ModalLoadPayload->ModalPromptText = ModalPromptText;
	ModalLoadPayload->Option1Text = Option1Text;
	ModalLoadPayload->Option2Text = Option2Text;

	PushContentToPrimaryLayoutWidgetLayer(LayerName, WidgetClass, ModalLoadPayload);

	// TODO: Complete this function with delegate binding for what to call when options are pressed in the modal

}

void AProject1HUDBase::BeginPlay()
{
	Super::BeginPlay();

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
