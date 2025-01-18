// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerInteractCollision.generated.h"

class UCapsuleComponent;

UCLASS()
class PROJECT1_API APlayerInteractCollision : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> CapsuleCollision{ nullptr };

public:	
	// Sets default values for this actor's properties
	APlayerInteractCollision();

	void SetCapsuleCollisionSize(float InRadius, float InHalfHeight);

	FORCEINLINE TObjectPtr<UCapsuleComponent> GetCapsuleCollision() { return CapsuleCollision; }
};
