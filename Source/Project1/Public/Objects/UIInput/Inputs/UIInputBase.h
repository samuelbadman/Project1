#pragma once

#include "CoreMinimal.h"
#include "Objects/Project1ObjectBase.h"
#include "UIInputBase.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class UEnhancedInputComponent;
class UInputMappingContext;

UCLASS(NotBlueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)
class PROJECT1_API UUIInputBase : public UProject1ObjectBase
{
	GENERATED_BODY()

public:
	virtual void SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent);

	void Add(TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem);
	void Remove(TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem);

private:
	virtual TObjectPtr<UInputMappingContext> GetInputMappingContext() const;
	virtual int32 GetInputPriority() const;
};