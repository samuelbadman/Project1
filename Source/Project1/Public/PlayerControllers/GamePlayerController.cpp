// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerCameraManagers/GamePlayerCameraManager.h"
#include "Components/ActorComponents/PlayerCharacterControllerComponent.h"
#include "Components/ActorComponents/PlayerInteractComponent.h"
#include "HUDs/GameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/ViewLockOnTargetInterface.h"

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
	GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Cyan, FString::Printf(TEXT("Look lock on input triggered")));

	GetPotentialLockOnTargets(PotentialLockOnTargets);

	for (IViewLockOnTargetInterface* Target : PotentialLockOnTargets)
	{
		// Get target as an actor
		AActor* const TargetActor{ Cast<AActor>(Target) };

		if (TargetActor)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Cyan, FString::Printf(TEXT("Found potential lock on target: %s"), *TargetActor->GetName()));
		}
	}
}

void AGamePlayerController::GetPotentialLockOnTargets(TArray<IViewLockOnTargetInterface*>& OutPotentialTargets)
{
	OutPotentialTargets.Empty();

	// Find actors inside camera view frustum
	const TObjectPtr<ULocalPlayer> LocalPlayer = GetLocalPlayer();

	if (!IsValid(LocalPlayer))
	{
		return;
	}

	const TObjectPtr<UGameViewportClient> ViewportClient = LocalPlayer->ViewportClient;
	if (!IsValid(ViewportClient))
	{
		return;
	}

	// Get scene view structure
	FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(ViewportClient->Viewport,
		World->Scene,
		ViewportClient->EngineShowFlags).SetRealtimeUpdate(true));

	FVector ViewLocation;
	FRotator ViewRotation;
	FSceneView* SceneView{ LocalPlayer->CalcSceneView(&ViewFamily, ViewLocation, ViewRotation, ViewportClient->Viewport) };

	if (SceneView == nullptr)
	{
		return;
	}

	TArray<AActor*> Actors{};
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), Actors);

	for (AActor* Actor : Actors)
	{
		// Ignore the player character actor as the player character can never be locked on to with the view
		if (GetPawn() == Actor)
		{
			continue;
		}

		// Does the actor implement the view lock on target interface, making it a valid lock on target?
		IViewLockOnTargetInterface* const ViewLockOnTargetInterface = Cast<IViewLockOnTargetInterface>(Actor);

		if (ViewLockOnTargetInterface == nullptr)
		{
			continue;
		}

		// Calculate the actor's bounds
		FVector ActorBoundsOrigin;
		FVector ActorBoundsExtent;
		Actor->GetActorBounds(false, ActorBoundsOrigin, ActorBoundsExtent, true);

		// Is the actor inside the scene view's frustum
		const bool ActorInView{ SceneView->ViewFrustum.IntersectBox(ActorBoundsOrigin, ActorBoundsExtent) };
		if (!ActorInView)
		{
			continue;
		}

		// Actor is valid lock on target. Add it to the array of potential targets
		OutPotentialTargets.Add(ViewLockOnTargetInterface);
	}
}
