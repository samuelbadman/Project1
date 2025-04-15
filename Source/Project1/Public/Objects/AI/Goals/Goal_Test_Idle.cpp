// Fill out your copyright notice in the Description page of Project Settings.


#include "Goal_Test_Idle.h"
#include "Goal_Common_Wait.h"
#include "Goal_Common_MoveToLocation.h"
#include "NavigationSystem.h"
#include "AI/Navigation/NavigationTypes.h"
#include "Actors/Pawns/Characters/Project1CharacterBase.h"
#include "NavigationPath.h"

UGoal_Test_Idle::UGoal_Test_Idle()
	: 
	bJustMoved(false)
{
}

void UGoal_Test_Idle::Start(TObjectPtr<AProject1AIControllerBase> AI)
{
	AddMoveToRandomReachablePointSubGoal(AI);
}

void UGoal_Test_Idle::ReevaluateSubGoal(TObjectPtr<AProject1AIControllerBase> AI)
{
	if (bJustMoved)
	{
		const TObjectPtr<UGoal_Common_Wait> WaitGoal{ AI->CreateGoal<UGoal_Common_Wait>(UGoal_Common_Wait::StaticClass()) };
		WaitGoal->Initialize(2.0f);

		AI->AddSubGoal(WaitGoal);
		bJustMoved = false;
	}
	else
	{
		AddMoveToRandomReachablePointSubGoal(AI);
	}
}

void UGoal_Test_Idle::AddMoveToRandomReachablePointSubGoal(TObjectPtr<AProject1AIControllerBase> AI)
{
	const TObjectPtr<UGoal_Common_MoveToLocation> MoveToLocationGoal{ AI->CreateGoal<UGoal_Common_MoveToLocation>(UGoal_Common_MoveToLocation::StaticClass()) };

	FNavLocation TargetMoveLocation;
	FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld())->GetRandomReachablePointInRadius(FVector::ZeroVector, 2048.0f, TargetMoveLocation);

	// Get path points from the AI pawn's current location and target move location. Will be helpful if implementing root motion navigation system.
	// Requires NavigationPath.h header for UNavigationPath object returned from FindPathToLocationSynchronously
	//const TObjectPtr<UNavigationPath> NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, AI->GetPawn()->GetActorLocation(), TargetMoveLocation);
	//DrawDebugSphere(GetWorld(), NavPath->PathPoints[0], 5.0f, 24, FColor::Red, false, 10.0f);
	//for(int32 i = 1; i < NavPath->PathPoints.Num(); ++i)
	//{
	//	DrawDebugSphere(GetWorld(), NavPath->PathPoints[i], 5.0f, 24, FColor::Green, false, 10.0f);
	//}

	MoveToLocationGoal->Initialize(TargetMoveLocation.Location, CastChecked<AProject1CharacterBase>(AI->GetCharacter())->GetLinearWalkSpeed(), 50.0f);

	AI->AddSubGoal(MoveToLocationGoal);
	bJustMoved = true;
}
