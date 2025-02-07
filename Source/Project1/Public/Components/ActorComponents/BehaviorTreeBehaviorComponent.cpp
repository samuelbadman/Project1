// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorTreeBehaviorComponent.h"
#include "AIController.h"

UBehaviorTreeBehaviorComponent::UBehaviorTreeBehaviorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBehaviorTreeBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

	// Try to run the behavior if the component owner is a pawn is not controlled by the player
	if (const TObjectPtr<APawn> PawnOwner = Cast<APawn>(GetOwner()))
	{
		// If pawn owner is not player controller
		if (!PawnOwner->IsPlayerControlled())
		{
			// Run behavior
			CastChecked<AAIController>(PawnOwner->GetController())->RunBehaviorTree(BehaviorTreeToRun);
		}
	}
}
