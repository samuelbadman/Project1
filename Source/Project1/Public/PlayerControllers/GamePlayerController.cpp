// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/ActorComponents/PlayerCharacterControllerComponent.h"

AGamePlayerController::AGamePlayerController()
{
	PlayerCharacterControllerComponent = CreateDefaultSubobject<UPlayerCharacterControllerComponent>(FName(TEXT("PlayerCharacterControllerComponent")));
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	const TObjectPtr<UEnhancedInputComponent> EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
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

	// TODO: Delay before adding mapping contexts at the start of the game as held inputs from old levels will trigger pressed inputs that are not wanted
	const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputLocalPlayerSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(MainInputMappingContext, MainInputMappingContextPriority);
}

void AGamePlayerController::OnJumpTriggered(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Cyan, FString::Printf(TEXT("Jump input triggered")));
}
