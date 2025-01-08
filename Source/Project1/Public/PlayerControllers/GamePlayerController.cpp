// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/ActorComponents/PlayerCharacterControllerComponent.h"
#include "PlayerCameraManagers/GamePlayerCameraManager.h"

AGamePlayerController::AGamePlayerController()
{
	PlayerCharacterControllerComponent = CreateDefaultSubobject<UPlayerCharacterControllerComponent>(FName(TEXT("PlayerCharacterControllerComponent")));
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	const TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(LookAbsoluteInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnLookAbsoluteTriggered);
	EnhancedInputComponent->BindAction(LookAnalogInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnLookAnalogTriggered);
	EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnJumpTriggered);
}

void AGamePlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	PlayerCharacterControllerComponent->SetupNewPossessedPawn(aPawn);
}

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Get player camera manager as game player camera manager
	GamePlayerCameraManager = CastChecked<AGamePlayerCameraManager>(PlayerCameraManager);

	// TODO: Delay before adding mapping contexts at the start of the game as held inputs from old levels will trigger pressed inputs that are not wanted
	const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputLocalPlayerSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(MainInputMappingContext, MainInputMappingContextPriority);
}

void AGamePlayerController::OnLookAbsoluteTriggered(const FInputActionValue& Value)
{
	// Look absolute is mapped to 2D mouse XY axis
	// Ignore mouse look inputs when the mouse cursor is visible
	if (IsMouseCursorVisible())
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Cyan, FString::Printf(TEXT("Look absolute value: %s"), *Value.Get<FVector2D>().ToString()));
	GamePlayerCameraManager->AddViewRotationFromInput(Value.Get<FVector2D>() * AbsoluteLookInputSensitivity);
}

void AGamePlayerController::OnLookAnalogTriggered(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Cyan, FString::Printf(TEXT("Look analog value: %s"), *Value.Get<FVector2D>().ToString()));
	GamePlayerCameraManager->AddViewRotationFromInput(Value.Get<FVector2D>() * AnalogLookInputSensitivity);
}

void AGamePlayerController::OnJumpTriggered(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Cyan, FString::Printf(TEXT("Jump input triggered")));
}
