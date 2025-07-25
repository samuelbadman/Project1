// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCameraManagers/GamePlayerCameraManager.h"
#include "Components/ActorComponents/PlayerInteractComponent.h"
#include "Components/ActorComponents/PlayerViewLockOnComponent.h"
#include "HUDs/GameHUD.h"
#include "Pawns/Characters/Project1CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Actors/Player/ArtificialPlayerLight.h"

AGamePlayerController::AGamePlayerController()
{
	PlayerInteractComponent = CreateDefaultSubobject<UPlayerInteractComponent>(FName(TEXT("PlayerInteractComponent")));
	PlayerViewLockOnComponent = CreateDefaultSubobject<UPlayerViewLockOnComponent>(FName(TEXT("PlayerViewLockOnComponent")));
}

void AGamePlayerController::ActivateArtificialPlayerLight(bool Activate)
{
	ArtificialPlayerLight->SetLightVisibility(Activate);
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	const TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent{ CastChecked<UEnhancedInputComponent>(InputComponent) };

	EnhancedInputComponent->BindAction(LookAbsoluteInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnLookAbsoluteTriggered);
	EnhancedInputComponent->BindAction(LookAnalogInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnLookAnalogTriggered);
	EnhancedInputComponent->BindAction(ResetLookInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnResetLookTriggered);
	EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnMoveTriggered);
	EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnJumpTriggered);
	EnhancedInputComponent->BindAction(OpenGameMenuInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnOpenGameMenuTriggered);
	EnhancedInputComponent->BindAction(LookLockOnInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnLookLockOnTriggered);
	EnhancedInputComponent->BindAction(SwitchLockTargetInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnSwitchLockTargetTriggered);
	EnhancedInputComponent->BindAction(ToggleWalkInputAction, ETriggerEvent::Triggered, this, &AGamePlayerController::OnToggleWalkTriggered);
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
	PossessedCharacter = CastChecked<AProject1CharacterBase>(aPawn);

	// Clear character use controller rotation settings
	PossessedCharacter->bUseControllerRotationPitch = false;
	PossessedCharacter->bUseControllerRotationYaw = false;
	PossessedCharacter->bUseControllerRotationRoll = false;

	// Do not rotate character with movement
	PossessedCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;

	// Player character mesh is only lit by lights affecting lighting channel 1. The player will only be lit by lights affecting lighting channel 1
	const TObjectPtr<USkeletalMeshComponent> CharacterMesh{ PossessedCharacter->GetMesh() };
	CharacterMesh->SetLightingChannels(0, 1, 0);

	// Setup player interact
	PlayerInteractComponent->OnPossessPawn(aPawn);

	// Setup artificial player light
	check(ArtificialPlayerLightClass != nullptr); // An artificial player light class must be set

	if (IsValid(ArtificialPlayerLight))
	{
		ArtificialPlayerLight->Destroy();
	}

	ArtificialPlayerLight = GetWorld()->SpawnActor<AArtificialPlayerLight>(ArtificialPlayerLightClass.LoadSynchronous(), FVector::ZeroVector, FRotator::ZeroRotator);
	ArtificialPlayerLight->AttachToActor(PossessedCharacter, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Get world
	World = GetWorld();

	// Get HUD
	GameHUD = CastChecked<AGameHUD>(GetHUD());

	// Add game input mapping contexts
	GetEnhancedInputLocalPlayerSubsystem()->AddMappingContext(LookInputMappingContext, LookInputMappingContextPriority);
	GetEnhancedInputLocalPlayerSubsystem()->AddMappingContext(ResetLookInputMappingContext, ResetLookInputMappingContextPriority);
	GetEnhancedInputLocalPlayerSubsystem()->AddMappingContext(MoveInputMappingContext, MoveInputMappingContextPriority);
	GetEnhancedInputLocalPlayerSubsystem()->AddMappingContext(JumpInputMappingContext, JumpInputMappingContextPriority);
	GetEnhancedInputLocalPlayerSubsystem()->AddMappingContext(OpenGameMenuInputMappingContext, OpenGameMenuInputMappingContextPriority);
	GetEnhancedInputLocalPlayerSubsystem()->AddMappingContext(LookLockOnInputMappingContext, LookLockOnInputMappingContextPriority);
	GetEnhancedInputLocalPlayerSubsystem()->AddMappingContext(ToggleWalkInputMappingContext, ToggleWalkInputMappingContextPriority);
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
	PossessedCharacter->SetTargetWorldOrientation(WorldMovementDirection.ToOrientationQuat(), false);
	PossessedCharacter->SetMovementSpeed((bLimitPlayerToWalk) ? 
		PossessedCharacter->GetLinearWalkSpeed() : (InputMagnitude < RunInputMagnitudeThreshold) ? 
			PossessedCharacter->GetLinearWalkSpeed() : PossessedCharacter->GetLinearRunSpeed());

	PossessedCharacter->AddMovementInput(WorldMovementDirection);
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

void AGamePlayerController::OnSwitchLockTargetTriggered(const FInputActionValue& Value)
{
	if (!IsValid(GamePlayerCameraManager))
	{
		return;
	}

	if (GamePlayerCameraManager->IsViewLocked())
	{
		PlayerViewLockOnComponent->OnSwitchLockTarget(Value.Get<float>(), this, GamePlayerCameraManager->GetViewWorldLocation());
	}
}

void AGamePlayerController::OnToggleWalkTriggered(const FInputActionValue& Value)
{
	bLimitPlayerToWalk = !bLimitPlayerToWalk;
}
