// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Project1AIControllerBase.generated.h"

class UAIGoalBase;
class UAICharacterControllerComponent;

/**
 *
 */
UCLASS()
class PROJECT1_API AProject1AIControllerBase : public AAIController
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAICharacterControllerComponent> AICharacterControllerComponent;

	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<UAIGoalBase> EntryTopGoalClass;

	UPROPERTY()
	TObjectPtr<UAIGoalBase> TopGoal;

	UPROPERTY()
	TArray<TObjectPtr<UAIGoalBase>> SubGoalQueue;

public:
	AProject1AIControllerBase();

	void SetTopGoal(TObjectPtr<UAIGoalBase> Goal);

	template<typename T>
	TObjectPtr<T> CreateGoal(const TSubclassOf<T>& GoalClass);
	TWeakObjectPtr<UAIGoalBase> AddSubGoal(TObjectPtr<UAIGoalBase> Goal);
	void RemoveSubGoal(const TWeakObjectPtr<UAIGoalBase>& Goal);
	void ClearSubGoals();

	FORCEINLINE TObjectPtr<UAICharacterControllerComponent> GetAICharacterController() const { return AICharacterControllerComponent; }

private:
	void OnPossess(APawn* InPawn) override;
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	void StartGoal(TObjectPtr<UAIGoalBase> Goal);
	void StopGoal(TObjectPtr<UAIGoalBase> Goal);
	void TickGoal(TObjectPtr<UAIGoalBase> Goal, float DeltaSeconds);
	void ReevaluateGoalSubGoal(TObjectPtr<UAIGoalBase> Goal);

	TObjectPtr<UAIGoalBase> GetTopSubGoal() const;
	void PopTopSubGoal();
	void EnqueueSubGoal(TObjectPtr<UAIGoalBase> Goal);
	void DequeueSubGoal(TObjectPtr<UAIGoalBase> Goal);
	bool IsSubGoalQueueEmpty() const;
};

template<typename T>
inline TObjectPtr<T> AProject1AIControllerBase::CreateGoal(const TSubclassOf<T>& GoalClass)
{
	return NewObject<T>(this, GoalClass);
}
