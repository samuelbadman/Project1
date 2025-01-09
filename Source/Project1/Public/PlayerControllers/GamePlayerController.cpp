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
	EnhancedInputComponent->BindAction(ResetLookInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnResetLookTriggered);
	EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnMoveTriggered);
	EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnJumpTriggered);
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
	PlayerCharacterControllerComponent->SetupNewPossessedPawn(aPawn);
}

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Get world
	World = GetWorld();

	// TODO: Delay before adding mapping contexts at the start of the game as held inputs from old levels will trigger pressed inputs that are not wanted
	const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputLocalPlayerSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(MainInputMappingContext, MainInputMappingContextPriority);
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

	GamePlayerCameraManager->AddViewRotationFromInput(Value.Get<FVector2D>() * AbsoluteLookInputSensitivity);
}

void AGamePlayerController::OnLookAnalogTriggered(const FInputActionValue& Value)
{
	if (!IsValid(GamePlayerCameraManager))
	{
		return;
	}

	GamePlayerCameraManager->AddViewRotationFromInput(Value.Get<FVector2D>() * AnalogLookInputSensitivity);
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
