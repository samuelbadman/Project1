// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCameraManagers/GamePlayerCameraManager.h"
#include "Components/ActorComponents/PlayerCharacterControllerComponent.h"
#include "Components/ActorComponents/PlayerInteractComponent.h"

AGamePlayerController::AGamePlayerController()
{
	PlayerCharacterControllerComponent = CreateDefaultSubobject<UPlayerCharacterControllerComponent>(FName(TEXT("PlayerCharacterControllerComponent")));
	PlayerInteractComponent = CreateDefaultSubobject<UPlayerInteractComponent>(FName(TEXT("PlayerInteractComponent")));
}

void AGamePlayerController::AddInteractPromptInputMappingContext()
{
	GetEnhancedInputLocalPlayerSubsystem()->AddMappingContext(InteractPromptInputMappingContext, InteractPromptInputPriority);
}

void AGamePlayerController::RemoveInteractPromptInputMappingContext()
{
	GetEnhancedInputLocalPlayerSubsystem()->RemoveMappingContext(InteractPromptInputMappingContext);
}

void AGamePlayerController::AddDialogueScreenInputMappingContext()
{
	GetEnhancedInputLocalPlayerSubsystem()->AddMappingContext(DialogueScreenInputMappingContext, DialogueScreenInputPriority);
}

void AGamePlayerController::RemoveDialogueScreenInputMappingContext()
{
	GetEnhancedInputLocalPlayerSubsystem()->RemoveMappingContext(DialogueScreenInputMappingContext);
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	const TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent{ CastChecked<UEnhancedInputComponent>(InputComponent) };

	EnhancedInputComponent->BindAction(InteractPromptInteractInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnInteractPromptUIInteractTriggered);
	EnhancedInputComponent->BindAction(InteractPromptSwitchActionInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnInteractPromptUISwitchActionTriggered);

	EnhancedInputComponent->BindAction(DialogueScreenConfirmInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnDialogueScreenConfirmTriggered);

	EnhancedInputComponent->BindAction(LookAbsoluteInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnLookAbsoluteTriggered);
	EnhancedInputComponent->BindAction(LookAnalogInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnLookAnalogTriggered);
	EnhancedInputComponent->BindAction(ResetLookInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnResetLookTriggered);
	EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnMoveTriggered);
	EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnJumpTriggered);
	EnhancedInputComponent->BindAction(OpenGameMenuInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnOpenGameMenuTriggered);
}

void AGamePlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	// Get player camera manager as game player camera manager if it is not already retrieved
	if (!IsValid(GamePlayerCameraManager))
	{
		GamePlayerCameraManager = CastChecked<AGamePlayerCameraManager>(PlayerCameraManager);
	}

	// Set player camera target actor to follow
	GamePlayerCameraManager->SetTargetFollowActor(aPawn);

	// Setup new possessed pawn
	PlayerCharacterControllerComponent->SetupNewPawn(aPawn);
	PlayerInteractComponent->SetupNewPawn(aPawn);
}

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Get world
	World = GetWorld();

	// Add game input mapping contexts
	const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputLocalPlayerSubsystem = GetEnhancedInputLocalPlayerSubsystem();

	EnhancedInputLocalPlayerSubsystem->AddMappingContext(LookInputMappingContext, LookInputMappingContextPriority);
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(ResetLookInputMappingContext, ResetLookInputMappingContextPriority);
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(MoveInputMappingContext, MoveInputMappingContextPriority);
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(JumpInputMappingContext, JumpInputMappingContextPriority);
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(OpenGameMenuInputMappingContext, OpenGameMenuInputMappingContextPriority);
}

void AGamePlayerController::OnInteractPromptUIInteractTriggered(const FInputActionValue& Value)
{
	InteractPromptInteractTriggered.Broadcast(Value);
}

void AGamePlayerController::OnInteractPromptUISwitchActionTriggered(const FInputActionValue& Value)
{
	InteractPromptSwitchActionTriggered.Broadcast(Value);
}

void AGamePlayerController::OnDialogueScreenConfirmTriggered(const FInputActionValue& Value)
{
	DialogueScreenConfirmTriggered.Broadcast(Value);
}

void AGamePlayerController::OnLookAbsoluteTriggered(const FInputActionValue& Value)
{
	if (!IsValid(GamePlayerCameraManager))
	{
		return;
	}

	// Look absolute is mapped to 2D mouse XY axis
	// Ignore mouse look inputs when the mouse cursor is visible
	if (IsMouseCursorVisible())
	{
		return;
	}

	GamePlayerCameraManager->AddImmediateViewRotation(Value.Get<FVector2D>() * AbsoluteLookInputSensitivity);
}

void AGamePlayerController::OnLookAnalogTriggered(const FInputActionValue& Value)
{
	if (!IsValid(GamePlayerCameraManager))
	{
		return;
	}

	GamePlayerCameraManager->AddViewRotation(Value.Get<FVector2D>() * AnalogLookInputSensitivity);
}

void AGamePlayerController::OnResetLookTriggered(const FInputActionValue& Value)
{
	if (!IsValid(GamePlayerCameraManager))
	{
		return;
	}

	GamePlayerCameraManager->ResetViewOrientation();
}

void AGamePlayerController::OnMoveTriggered(const FInputActionValue& Value)
{
	if (!IsValid(GamePlayerCameraManager))
	{
		return;
	}

	FVector InputVector{ Value.Get<FVector>() };
	const float InputMagnitude{ Value.GetMagnitude() };

	// Get input direction in world space
	// World forward is the +x axis and world right is +y axis. Input forward is +y axis and input right is +x axis. Swap vector components.
	Swap(InputVector.X, InputVector.Y);

	// Get yaw orientation of the view on the current frame
	const FQuat ViewYawOrientation{ GamePlayerCameraManager->GetViewYawOrientation() };

	// Get world movement direction on ground plane from input values relative to the camera's orientation on the yaw plane
	const FVector WorldMovementDirection{ ViewYawOrientation.RotateVector(InputVector).GetSafeNormal() };

	// Add view yaw scaled by the amount of right input that will not be processed until the next input frame
	const FVector ViewYawDirection{ ViewYawOrientation.Vector() };
	const double ViewYawOffset{ FMath::Abs(1.0 -
		FMath::Abs(FVector2D::DotProduct(FVector2D(WorldMovementDirection.X, WorldMovementDirection.Y), FVector2D(ViewYawDirection.X, ViewYawDirection.Y)))) };
	const double Sign = -1.0 * FMath::Sign(FVector::DotProduct(FVector::CrossProduct(ViewYawDirection, FVector::UpVector).GetSafeNormal(), WorldMovementDirection));

	GamePlayerCameraManager->AddViewYawRotation(MoveRightViewYawRotationRate * (ViewYawOffset * Sign) * World->DeltaTimeSeconds);

	// Add movement input
	PlayerCharacterControllerComponent->AddMovement(WorldMovementDirection, InputMagnitude);
}

void AGamePlayerController::OnJumpTriggered(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Cyan, FString::Printf(TEXT("Jump input triggered")));
}

void AGamePlayerController::OnOpenGameMenuTriggered(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Cyan, FString::Printf(TEXT("Open game menu input triggered")));
}
