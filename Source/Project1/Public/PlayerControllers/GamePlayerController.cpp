// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	const TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(TestInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnTestInputActionTriggered);
}

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputLocalPlayerSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(MainInputMappingContext, MainInputMappingContextPriority);
}

void AGamePlayerController::OnTestInputActionTriggered(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Green, FString::Printf(TEXT("Test input action triggered")));
}
