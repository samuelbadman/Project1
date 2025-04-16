#include "UIInputBase.h"
#include "EnhancedInputSubsystems.h"

void UUIInputBase::SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent)
{
	// Base class implementation is empty
}

void UUIInputBase::Add(TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem)
{
	InputSubsystem->AddMappingContext(GetInputMappingContext(), GetInputPriority());
}

void UUIInputBase::Remove(TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem)
{
	InputSubsystem->RemoveMappingContext(GetInputMappingContext());
}

TObjectPtr<UInputMappingContext> UUIInputBase::GetInputMappingContext() const
{
	// Base class implementation is empty
	return nullptr;
}

int32 UUIInputBase::GetInputPriority() const
{
	// Base class implementation is empty
	return 0;
}
