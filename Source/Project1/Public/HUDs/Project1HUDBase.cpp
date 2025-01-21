// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1HUDBase.h"
#include "UserWidgets/PrimaryLayouts/PrimaryLayoutUserWidgetBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/UIInputMapping.h"
#include "GameViewportClients/Project1GameViewportClientBase.h"
#include "Kismet/GameplayStatics.h"

void AProject1HUDBase::PushContentToPrimaryLayoutLayer(const FGameplayTag& LayerName, const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass)
{
	PrimaryLayoutWidget->PushContentToLayer(LayerName, WidgetClass);
}

void AProject1HUDBase::PopContentFromPrimaryLayoutLayer(const FGameplayTag& LayerName)
{
	PrimaryLayoutWidget->PopContentFromLayer(LayerName);
}

ULayerUserWidgetBase* AProject1HUDBase::GetRegisteredPrimaryLayoutLayer(const FGameplayTag& LayerName)
{
	return PrimaryLayoutWidget->GetRegisteredLayer(LayerName);
}

void AProject1HUDBase::SetActiveInputPrimaryLayoutLayer(const FGameplayTag& LayerName)
{
	PrimaryLayoutWidget->SetActiveInputLayer(LayerName);
}

const FGameplayTag& AProject1HUDBase::GetPreviousActiveInputPrimaryLayoutLayer() const
{
	return PrimaryLayoutWidget->GetPreviousActiveInputLayerName();
}

bool AProject1HUDBase::IsContentOnTopOfPrimaryLayoutLayer(const FGameplayTag& LayerName, TObjectPtr<UScreenUserWidgetBase> Widget) const
{
	return PrimaryLayoutWidget->IsContentOnTopOfLayer(LayerName, Widget);
}

void AProject1HUDBase::BindUIInputActions(UEnhancedInputComponent* EnhancedInputComponent)
{
	// Bind UI input actions/values
	if (IsValid(UIInputMapping))
	{
		EnhancedInputComponent->BindAction(UIInputMapping->GetLeftClickInputAction(), ETriggerEvent::Triggered, this, &AProject1HUDBase::OnLeftClickTriggered);
		EnhancedInputComponent->BindAction(UIInputMapping->GetRightClickInputAction(), ETriggerEvent::Triggered, this, &AProject1HUDBase::OnRightClickTriggered);
		EnhancedInputComponent->BindAction(UIInputMapping->GetMiddleClickInputAction(), ETriggerEvent::Triggered, this, &AProject1HUDBase::OnMiddleClickTriggered);
		EnhancedInputComponent->BindAction(UIInputMapping->GetMouseWheelInputAction(), ETriggerEvent::Triggered, this, &AProject1HUDBase::OnMouseWheelTriggered);
		EnhancedInputComponent->BindAction(UIInputMapping->GetNavigateInputAction(), ETriggerEvent::Triggered, this, &AProject1HUDBase::OnNavigateTriggered);
		EnhancedInputComponent->BindAction(UIInputMapping->GetNavigateNoMoveInputAction(), ETriggerEvent::Triggered, this, &AProject1HUDBase::OnNavigateNoMoveTriggered);
		EnhancedInputComponent->BindAction(UIInputMapping->GetNavigateNoMoveNoRepeatInputAction(), ETriggerEvent::Triggered, this, &AProject1HUDBase::OnNavigateNoMoveNoRepeatTriggered);
		EnhancedInputComponent->BindAction(UIInputMapping->GetConfirmInputAction(), ETriggerEvent::Triggered, this, &AProject1HUDBase::OnConfirmTriggered);
		EnhancedInputComponent->BindAction(UIInputMapping->GetCancelInputAction(), ETriggerEvent::Triggered, this, &AProject1HUDBase::OnCancelTriggered);
		EnhancedInputComponent->BindAction(UIInputMapping->GetTabInputAction(), ETriggerEvent::Triggered, this, &AProject1HUDBase::OnTabTriggered);
		EnhancedInputComponent->BindAction(UIInputMapping->GetAnyInputInputAction(), ETriggerEvent::Triggered, this, &AProject1HUDBase::OnAnyInputTriggered);
	}
}

void AProject1HUDBase::BindToMouseMoveEvents(UProject1GameViewportClientBase* Project1GameViewportClient)
{
	// Bind to game viewport client generated mouse move events
	OnMouseMovedDelegateHandle = Project1GameViewportClient->GetOnMouseMovedDelegate().AddUObject(this, &AProject1HUDBase::OnMouseMoved);
}

void AProject1HUDBase::UnbindFromMouseMoveEvents(UProject1GameViewportClientBase* Project1GameViewportClient)
{
	// Remove binding to game viewport client generated mouse move events
	Project1GameViewportClient->GetOnMouseMovedDelegate().Remove(OnMouseMovedDelegateHandle);
	OnMouseMovedDelegateHandle.Reset();
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

void AProject1HUDBase::OnMouseMoved(const FVector2D& NewMousePosition, const FVector2D& OldMousePosition, const FVector2D& MouseMoveDelta)
{
	PrimaryLayoutWidget->RouteOnMouseMoved(NewMousePosition, OldMousePosition, MouseMoveDelta);
}

void AProject1HUDBase::OnLeftClickTriggered(const FInputActionValue& Value)
{
	PrimaryLayoutWidget->RouteOnLeftClickTriggered(Value);
}

void AProject1HUDBase::OnMiddleClickTriggered(const FInputActionValue& Value)
{
	PrimaryLayoutWidget->RouteOnMiddleClickTriggered(Value);
}

void AProject1HUDBase::OnRightClickTriggered(const FInputActionValue& Value)
{
	PrimaryLayoutWidget->RouteOnRightClickTriggered(Value);
}

void AProject1HUDBase::OnMouseWheelTriggered(const FInputActionValue& Value)
{
	PrimaryLayoutWidget->RouteOnMouseWheelTriggered(Value);
}

void AProject1HUDBase::OnNavigateTriggered(const FInputActionValue& Value)
{
	PrimaryLayoutWidget->RouteOnNavigateTriggered(Value);
}

void AProject1HUDBase::OnNavigateNoMoveTriggered(const FInputActionValue& Value)
{
	PrimaryLayoutWidget->RouteOnNavigateNoMoveTriggered(Value);
}

void AProject1HUDBase::OnNavigateNoMoveNoRepeatTriggered(const FInputActionValue& Value)
{
	PrimaryLayoutWidget->RouteOnNavigateNoMoveNoRepeatTriggered(Value);
}

void AProject1HUDBase::OnConfirmTriggered(const FInputActionValue& Value)
{
	PrimaryLayoutWidget->RouteOnConfirmTriggered(Value);
}

void AProject1HUDBase::OnCancelTriggered(const FInputActionValue& Value)
{
	PrimaryLayoutWidget->RouteOnCancelTriggered(Value);
}

void AProject1HUDBase::OnTabTriggered(const FInputActionValue& Value)
{
	PrimaryLayoutWidget->RouteOnTabTriggered(Value);
}

void AProject1HUDBase::OnAnyInputTriggered(const FInputActionValue& Value)
{
	PrimaryLayoutWidget->RouteOnAnyInputTriggered(Value);
}
