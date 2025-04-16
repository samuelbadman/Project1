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

private:
	UPROPERTY(EditDefaultsOnly, Category = "Input Mapping")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input Mapping")
	int32 InputPriority;

public:
	UUIInputBase();

	virtual void SetupInput(TObjectPtr<UEnhancedInputComponent> InputComponent);

	void Add(TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem);
	void Remove(TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem);
};