// Fill out your copyright notice in the Description page of Project Settings.


#include "Goal_Test_Idle.h"
#include "Goal_Common_Wait.h"
#include "Goal_Common_MoveToLocation.h"

void UGoal_Test_Idle::Start(TObjectPtr<AProject1AIControllerBase> AI)
{
	const TObjectPtr<UGoal_Common_MoveToLocation> MoveToLocationGoal{ AI->CreateGoal<UGoal_Common_MoveToLocation>(UGoal_Common_MoveToLocation::StaticClass()) };
	MoveToLocationGoal->Initialize(FVector::ZeroVector);
	AI->AddSubGoal(MoveToLocationGoal);
}

void UGoal_Test_Idle::ReevaluateSubGoal(TObjectPtr<AProject1AIControllerBase> AI)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("%s reevaluating sub goal"), *GetName()));
}
