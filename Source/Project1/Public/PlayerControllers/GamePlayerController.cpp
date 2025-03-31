// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCameraManagers/GamePlayerCameraManager.h"
#include "Components/ActorComponents/PlayerCharacterControllerComponent.h"
#include "Components/ActorComponents/PlayerInteractComponent.h"
#include "Components/ActorComponents/PlayerViewLockOnComponent.h"
#include "HUDs/GameHUD.h"

AGamePlayerController::AGamePlayerController()
{
	PlayerCharacterControllerComponent = CreateDefaultSubobject<UPlayerCharacterControllerComponent>(FName(TEXT("PlayerCharacterControllerComponent")));
	PlayerInteractComponent = CreateDefaultSubobject<UPlayerInteractComponent>(FName(TEXT("PlayerInteractComponent")));
	PlayerViewLockOnComponent = CreateDefaultSubobject<UPlayerViewLockOnComponent>(FName(TEXT("PlayerViewLockOnComponent")));
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

void AGamePlayerController::AddGameMenuInputMappingContext()
{
	GetEnhancedInputLocalPlayerSubsystem()->AddMappingContext(GameMenuScreenInputMappingContext, GameMenuScreenInputPriority);
}

void AGamePlayerController::RemoveGameMenuInputMappingContext()
{
	GetEnhancedInputLocalPlayerSubsystem()->RemoveMappingContext(GameMenuScreenInputMappingContext);
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	const TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent{ CastChecked<UEnhancedInputComponent>(InputComponent) };

	EnhancedInputComponent->BindAction(InteractPromptInteractInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnInteractPromptUIInteractTriggered);
	EnhancedInputComponent->BindAction(InteractPromptSwitchActionInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnInteractPromptUISwitchActionTriggered);

	EnhancedInputComponent->BindAction(DialogueScreenConfirmInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnDialogueScreenConfirmTriggered);

	EnhancedInputComponent->BindAction(GameMenuScreenConfirmInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnGameMenuScreenConfirmTriggered);
	EnhancedInputComponent->BindAction(GameMenuScreenNavigateInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnGameMenuScreenNavigateTriggered);
	EnhancedInputComponent->BindAction(GameMenuScreenCancelInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnGameMenuScreenCancelTriggered);
	EnhancedInputComponent->BindAction(GameMenuScreenQuitInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnGameMenuScreenQuitTriggered);

	EnhancedInputComponent->BindAction(LookAbsoluteInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnLookAbsoluteTriggered);
	EnhancedInputComponent->BindAction(LookAnalogInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnLookAnalogTriggered);
	EnhancedInputComponent->BindAction(ResetLookInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnResetLookTriggered);
	EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnMoveTriggered);
	EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnJumpTriggered);
	EnhancedInputComponent->BindAction(OpenGameMenuInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnOpenGameMenuTriggered);
	EnhancedInputComponent->BindAction(LookLockOnInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnLookLockOnTriggered);
}

void AGamePlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	// Get player camera manager as game player camera manager if it is not already retrieved
	if (!IsValid(GamePlayerCameraManager))
	{
		GamePlayerCameraManager = CastChecked<AGamePlayerCameraManager>(PlayerCameraManager);
		PlayerViewLockOnComponent->SetGamePlayerCameraManager(GamePlayerCameraManager);
	}

	// Set player camera target actor to follow
	GamePlayerCameraManager->SetTargetFollowActor(aPawn);

	// Setup new possessed pawn
	PlayerCharacterControllerComponent->OnPossessPawn(aPawn);
	PlayerInteractComponent->OnPossessPawn(aPawn);
}

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Get world
	World = GetWorld();

	// Get HUD
	GameHUD = CastChecked<AGameHUD>(GetHUD());

	// Add game input mapping contexts
	const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputLocalPlayerSubsystem = GetEnhancedInputLocalPlayerSubsystem();

	EnhancedInputLocalPlayerSubsystem->AddMappingContext(LookInputMappingContext, LookInputMappingContextPriority);
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(ResetLookInputMappingContext, ResetLookInputMappingContextPriority);
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(MoveInputMappingContext, MoveInputMappingContextPriority);
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(JumpInputMappingContext, JumpInputMappingContextPriority);
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(OpenGameMenuInputMappingContext, OpenGameMenuInputMappingContextPriority);
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(LookLockOnInputMappingContext, LookLockOnInputMappingContextPriority);
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

void AGamePlayerController::OnGameMenuScreenConfirmTriggered(const FInputActionValue& Value)
{
	GameMenuScreenConfirmTriggered.Broadcast(Value);
}

void AGamePlayerController::OnGameMenuScreenNavigateTriggered(const FInputActionValue& Value)
{
	GameMenuScreenNavigateTriggered.Broadcast(Value);
}

void AGamePlayerController::OnGameMenuScreenCancelTriggered(const FInputActionValue& Value)
{
	GameMenuScreenCancelTriggered.Broadcast(Value);
}

void AGamePlayerController::OnGameMenuScreenQuitTriggered(const FInputActionValue& Value)
{
	GameMenuScreenQuitTriggered.Broadcast(Value);
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
	//const FVector ViewYawDirection{ ViewYawOrientation.Vector() };
	//const double ViewYawOffset{ FMath::Abs(1.0 -
	//	FMath::Abs(FVector2D::DotProduct(FVector2D(WorldMovementDirection.X, WorldMovementDirection.Y), FVector2D(ViewYawDirection.X, ViewYawDirection.Y)))) };
	//const double Sign = -1.0 * FMath::Sign(FVector::DotProduct(FVector::CrossProduct(ViewYawDirection, FVector::UpVector).GetSafeNormal(), WorldMovementDirection));

	//GamePlayerCameraManager->AddViewYawRotation(MoveRightViewYawRotationRate * (ViewYawOffset * Sign) * World->DeltaTimeSeconds);

	// Add movement input
	PlayerCharacterControllerComponent->OnMoveInput(WorldMovementDirection, InputMagnitude);
}

void AGamePlayerController::OnJumpTriggered(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Cyan, FString::Printf(TEXT("Jump input triggered")));
}

void AGamePlayerController::OnOpenGameMenuTriggered(const FInputActionValue& Value)
{
	GameHUD->OpenGameMenu();
}

void AGamePlayerController::OnLookLockOnTriggered(const FInputActionValue& Value)
{
	PlayerViewLockOnComponent->OnLockOnInput(this, GamePlayerCameraManager->GetViewWorldLocation());
}
