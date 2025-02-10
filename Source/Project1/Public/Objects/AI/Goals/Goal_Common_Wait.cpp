// Fill out your copyright notice in the Description page of Project Settings.


#include "Goal_Common_Wait.h"

UGoal_Common_Wait::UGoal_Common_Wait()
{
	Duration = 0.0f;
	OwnerAI = nullptr;
	WorldTimerManager = nullptr;
	WaitTimerHandle = {};
}

void UGoal_Common_Wait::Stop(TObjectPtr<AProject1AIControllerBase> AI)
{
	WorldTimerManager->ClearTimer(WaitTimerHandle);
}

void UGoal_Common_Wait::Start(TObjectPtr<AProject1AIControllerBase> AI)
{
	OwnerAI = AI;
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	WorldTimerManager = &TimerManager;
	TimerManager.SetTimer(WaitTimerHandle, this, &UGoal_Common_Wait::OnDurationElapsed, Duration, false);
}

void UGoal_Common_Wait::OnDurationElapsed()
{
	OwnerAI->RemoveSubGoal(this);
}

void UGoal_Common_Wait::Initialize(float InDuration)
{
	Duration = InDuration;
}
