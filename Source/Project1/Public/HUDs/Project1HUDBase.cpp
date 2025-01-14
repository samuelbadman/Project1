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

bool AProject1HUDBase::IsContentOnTopOfPrimaryLayoutLayer(const FGameplayTag& LayerName, TObjectPtr<UScreenUserWidgetBase> Widget) const
{
	return PrimaryLayoutWidget->IsContentOnTopOfLayer(LayerName, Widget);
}

void AProject1HUDBase::SetUIInputsEnabled(bool Enable)
{
	if (!IsValid(UIInputMapping))
	{
		return;
	}

	if (Enable)
	{
		// Bind to game viewport client generated mouse move events
		OnMouseMovedDelegateHandle = ProjectGameViewportClient->GetOnMouseMovedDelegate().AddUObject(this, &AProject1HUDBase::OnMouseMoved);

		// Add UI input mapping context
		EnhancedInputLocalPlayerSubsystem->AddMappingContext(UIInputMapping->GetUIInputMappingContext(), UIInputMapping->GetUIInputMappingContextPriority());
	}
	else
	{
		// Remove binding to game viewport client generated mouse move events
		ProjectGameViewportClient->GetOnMouseMovedDelegate().Remove(OnMouseMovedDelegateHandle);
		OnMouseMovedDelegateHandle = {};

		// Remove UI input mapping context
		EnhancedInputLocalPlayerSubsystem->RemoveMappingContext(UIInputMapping->GetUIInputMappingContext());
	}
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

	// Get owning player controller
	const TObjectPtr<APlayerController> OwningPlayerController{ GetOwningPlayerController() };

	// Get reference to enhanced input local player subsystem
	EnhancedInputLocalPlayerSubsystem = OwningPlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	// Get reference to game viewport client as project game viewport client
	ProjectGameViewportClient = CastChecked<UProject1GameViewportClientBase>(UGameplayStatics::GetGameInstance(this)->GetGameViewportClient());

	// Bind UI input actions/values
	if (IsValid(UIInputMapping))
	{
		const TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(OwningPlayerController->InputComponent);
		EnhancedInputComponent->BindAction(UIInputMapping->GetLeftClickInputAction(), ETriggerEvent::Triggered, this, &AProject1HUDBase::OnLeftClickTriggered);
		EnhancedInputComponent->BindAction(UIInputMapping->GetRightClickInputAction(), ETriggerEvent::Triggered, this, &AProject1HUDBase::OnRightClickTriggered);
		EnhancedInputComponent->BindAction(UIInputMapping->GetMiddleClickInputAction(), ETriggerEvent::Triggered, this, &AProject1HUDBase::OnMiddleClickTriggered);
		EnhancedInputComponent->BindAction(UIInputMapping->GetMouseWheelInputAction(), ETriggerEvent::Triggered, this, &AProject1HUDBase::OnMouseWheelTriggered);
		EnhancedInputComponent->BindAction(UIInputMapping->GetNavigateInputAction(), ETriggerEvent::Triggered, this, &AProject1HUDBase::OnNavigateTriggered);
		EnhancedInputComponent->BindAction(UIInputMapping->GetConfirmInputAction(), ETriggerEvent::Triggered, this, &AProject1HUDBase::OnConfirmTriggered);
		EnhancedInputComponent->BindAction(UIInputMapping->GetCancelInputAction(), ETriggerEvent::Triggered, this, &AProject1HUDBase::OnCancelTriggered);
		EnhancedInputComponent->BindAction(UIInputMapping->GetTabInputAction(), ETriggerEvent::Triggered, this, &AProject1HUDBase::OnTabTriggered);
		EnhancedInputComponent->BindAction(UIInputMapping->GetAnyInputInputAction(), ETriggerEvent::Triggered, this, &AProject1HUDBase::OnAnyInputTriggered);
	}
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
