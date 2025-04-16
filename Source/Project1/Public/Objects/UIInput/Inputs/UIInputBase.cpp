#include "UIInputBase.h"
#include "EnhancedInputSubsystems.h"

UUIInputBase::UUIInputBase()
	: 
	InputMappingContext(nullptr),
	InputPriority(0)
{
}

void UUIInputBase::SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent)
{
	// Base class implementation is empty
}

void UUIInputBase::Add(TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem)
{
	InputSubsystem->AddMappingContext(InputMappingContext, InputPriority);
}

void UUIInputBase::Remove(TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem)
{
	InputSubsystem->RemoveMappingContext(InputMappingContext);
}
