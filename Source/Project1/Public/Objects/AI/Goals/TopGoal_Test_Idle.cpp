// Fill out your copyright notice in the Description page of Project Settings.


#include "TopGoal_Test_Idle.h"
#include "Goal_Common_Wait.h"

void UTopGoal_Test_Idle::Start(TObjectPtr<AProject1AIControllerBase> AI)
{
	const TObjectPtr<UGoal_Common_Wait> WaitGoal{ AI->CreateGoal<UGoal_Common_Wait>(UGoal_Common_Wait::StaticClass()) };
	WaitGoal->Initialize(2.0f);
	AI->AddSubGoal(WaitGoal);
}

void UTopGoal_Test_Idle::ReevaluateSubGoal(TObjectPtr<AProject1AIControllerBase> AI)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::White, FString::Printf(TEXT("%s reevaluating sub goal"), *GetName()));
}
