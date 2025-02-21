// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/Characters/Project1CharacterBase.h"
#include "PlayerCharacterBase.generated.h"

class UPointLightComponent;

/**
 * 
 */
UCLASS()
class PROJECT1_API APlayerCharacterBase : public AProject1CharacterBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPointLightComponent> GlowPointLight;

public:
	APlayerCharacterBase(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "PlayerCharacter")
	void SetGlowLightVisibility(const bool NewVisibility);

private:
	void Move(const FVector& DesiredDirection) override;
};
