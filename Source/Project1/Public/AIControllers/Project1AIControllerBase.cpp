// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1AIControllerBase.h"
#include "Objects/AI/Goals/AIGoalBase.h"
#include "Components/ActorComponents/AICharacterControllerComponent.h"

AProject1AIControllerBase::AProject1AIControllerBase()
{
	PrimaryActorTick.bCanEverTick = true;
	AICharacterControllerComponent = CreateDefaultSubobject<UAICharacterControllerComponent>(FName(TEXT("AICharacterControllerComponent")));
	EntryTopGoalClass = nullptr;
	TopGoal = nullptr;
	SubGoalQueue = {};
}

void AProject1AIControllerBase::SetTopGoal(TObjectPtr<UAIGoalBase> Goal)
{
	// Stop current active top goal if there is one
	if (IsValid(TopGoal))
	{
		StopGoal(TopGoal);
	}
	// Start the new top goal if it is valid
	TopGoal = Goal;
	if (IsValid(Goal))
	{
		StartGoal(Goal);
		if (IsSubGoalQueueEmpty())
		{
			ReevaluateGoalSubGoal(Goal);
		}
	}
}

TWeakObjectPtr<UAIGoalBase> AProject1AIControllerBase::AddSubGoal(TObjectPtr<UAIGoalBase> Goal)
{
	if (SubGoalQueue.Num() == 0)
	{
		// Goal will be at the front of the queue and needs to be immediately started
		StartGoal(Goal);
	}
	EnqueueSubGoal(Goal);
	return Goal;
}

void AProject1AIControllerBase::RemoveSubGoal(const TWeakObjectPtr<UAIGoalBase>& Goal)
{
	const TObjectPtr<UAIGoalBase> GoalObj{ Goal.Get() };
	if (GetTopSubGoal() == GoalObj)
	{
		StopGoal(GoalObj);
	}
	DequeueSubGoal(GoalObj);
	const TObjectPtr<UAIGoalBase> NewTopSubGoal{ GetTopSubGoal() };
	if (IsValid(NewTopSubGoal))
	{
		StartGoal(NewTopSubGoal);
	}
	else
	{
		ReevaluateGoalSubGoal(TopGoal);
	}
}

void AProject1AIControllerBase::ClearSubGoals()
{
	const TObjectPtr<UAIGoalBase> TopSubGoal{ GetTopSubGoal() };
	if (IsValid(TopSubGoal))
	{
		StopGoal(TopSubGoal);
	}
	SubGoalQueue.Empty();
	ReevaluateGoalSubGoal(TopGoal);
}

void AProject1AIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AICharacterControllerComponent->SetupNewPawn(InPawn);
}

void AProject1AIControllerBase::BeginPlay()
{
	Super::BeginPlay();
	if (const TSubclassOf<UAIGoalBase> LoadedEntryTopGoalClass = EntryTopGoalClass.LoadSynchronous())
	{
		SetTopGoal(CreateGoal<UAIGoalBase>(LoadedEntryTopGoalClass));
	}
}

void AProject1AIControllerBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// Tick active top goal
	if (IsValid(TopGoal))
	{
		TickGoal(TopGoal, DeltaSeconds);
	}
	// Tick top sub goal
	if (const TObjectPtr<UAIGoalBase> TopSubGoal = GetTopSubGoal())
	{
		TickGoal(TopSubGoal, DeltaSeconds);
	}
}

TObjectPtr<UAIGoalBase> AProject1AIControllerBase::GetTopSubGoal() const
{
	if (SubGoalQueue.IsEmpty())
	{
		return nullptr;
	}
	return SubGoalQueue[0];
}

void AProject1AIControllerBase::PopTopSubGoal()
{
	SubGoalQueue.RemoveAt(0);
}

void AProject1AIControllerBase::EnqueueSubGoal(TObjectPtr<UAIGoalBase> Goal)
{
	SubGoalQueue.Add(Goal);
}

void AProject1AIControllerBase::DequeueSubGoal(TObjectPtr<UAIGoalBase> Goal)
{
	SubGoalQueue.RemoveSingle(Goal);
}

bool AProject1AIControllerBase::IsSubGoalQueueEmpty() const
{
	return SubGoalQueue.IsEmpty();
}

void AProject1AIControllerBase::StartGoal(TObjectPtr<UAIGoalBase> Goal)
{
	Goal->Start(this);
}

void AProject1AIControllerBase::StopGoal(TObjectPtr<UAIGoalBase> Goal)
{
	Goal->Stop(this);
}

void AProject1AIControllerBase::TickGoal(TObjectPtr<UAIGoalBase> Goal, float DeltaSeconds)
{
	Goal->Tick(this, DeltaSeconds);
}

void AProject1AIControllerBase::ReevaluateGoalSubGoal(TObjectPtr<UAIGoalBase> Goal)
{
	Goal->ReevaluateSubGoal(this);
}
