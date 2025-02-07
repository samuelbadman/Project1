// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponents/Project1ActorComponentBase.h"
#include "BehaviorTreeBehaviorComponent.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECT1_API UBehaviorTreeBehaviorComponent : public UProject1ActorComponentBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBehaviorTree> BehaviorTreeToRun{ nullptr };

public:
	UBehaviorTreeBehaviorComponent();

private:
	void BeginPlay() override;
};
