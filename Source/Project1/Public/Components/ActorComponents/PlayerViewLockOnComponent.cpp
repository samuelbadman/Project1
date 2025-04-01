// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerViewLockOnComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/ViewLockOnTargetInterface.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "PlayerCameraManagers/GamePlayerCameraManager.h"

UPlayerViewLockOnComponent::UPlayerViewLockOnComponent()
	:
	ViewLockMaxDepth(2500.0f),
	World(GetWorld()),
	OverMaxDepthCheckTimerHandle({}),
	OverMaxDepthCheckIntervalSeconds(0.001f)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerViewLockOnComponent::OnLockOnInput(TObjectPtr<APlayerController> PlayerController, const FVector& ViewWorldLocation)
{
	if (!GamePlayerCameraManager->IsViewLocked())
	{
		// Find potential lock on targets
		TArray<IViewLockOnTargetInterface*> PotentialLockOnTargets{};
		GetPotentialLockOnTargets(PlayerController, ViewWorldLocation, PotentialLockOnTargets);

		// Select which potential target to lock on to
		// Lock on to the target closest to the center of the view on the horizontal axis
		const FVector2D ViewportCenter{ UWidgetLayoutLibrary::GetViewportSize(World) * 0.5f };

		const int32 NumPotentialLockOnTargets{ PotentialLockOnTargets.Num() };
		TArray<float> TargetDistances{};
		TargetDistances.SetNumZeroed(NumPotentialLockOnTargets);
		for (int32 i = 0; i < NumPotentialLockOnTargets; ++i)
		{
			// Get target as an actor
			AActor* const TargetActor{ Cast<AActor>(PotentialLockOnTargets[i]) };

			if (TargetActor)
			{
				const FVector TargetActorWorldSpaceLocation{ TargetActor->GetActorLocation() };

				// Get target actor screen space location
				FVector2D ActorScreenLocation;
				PlayerController->ProjectWorldLocationToScreen(TargetActorWorldSpaceLocation, ActorScreenLocation);

				// Calculate the distance from the center of the view to the actor's screen space location on the horizontal axis
				TargetDistances[i] = StaticCast<float>((ActorScreenLocation - ViewportCenter).SquaredLength());
			}
			else
			{
				TargetDistances[i] = UE_BIG_NUMBER;
			}
		}

		// Get the index of the minimum distance value
		const int32 ClosestIndex{ TargetDistances.Find(FMath::Min(TargetDistances)) };

		if (PotentialLockOnTargets.IsValidIndex(ClosestIndex))
		{
			// Lock on to target
			LockView(Cast<AActor>(PotentialLockOnTargets[ClosestIndex]));
		}
	}
	else
	{
		// Is locked on so unlock view from its current target
		UnlockView();
	}
}

void UPlayerViewLockOnComponent::OnSwitchLockTarget(float InputValue, TObjectPtr<APlayerController> PlayerController, const FVector& ViewWorldLocation)
{
	// Find potential lock on targets
	TArray<IViewLockOnTargetInterface*> PotentialLockOnTargets{};
	GetPotentialLockOnTargets(PlayerController, ViewWorldLocation, PotentialLockOnTargets);

	// Sort potential lock on targets into ascending order along the horizontal screen axis
	Algo::Sort(PotentialLockOnTargets, [PlayerController](IViewLockOnTargetInterface* A, IViewLockOnTargetInterface* B) {
		const TObjectPtr<const AActor> TargetActorA{ Cast<AActor>(A) };
		const TObjectPtr<const AActor> TargetActorB{ Cast<AActor>(B) };

		if (!IsValid(TargetActorA) ||
			!IsValid(TargetActorB))
		{
			return false;
		}

		// Calculate the horizontal axis screen space location of targets A and B
		FVector2D ScreenSpaceLocationA;
		PlayerController->ProjectWorldLocationToScreen(TargetActorA->GetActorLocation(), ScreenSpaceLocationA);

		FVector2D ScreenSpaceLocationB;
		PlayerController->ProjectWorldLocationToScreen(TargetActorB->GetActorLocation(), ScreenSpaceLocationB);

		return (ScreenSpaceLocationA.X < ScreenSpaceLocationB.X);
		});

	// Find location (index) of current locked on target in sorted array
	const int32 CurrentTargetIndex{ PotentialLockOnTargets.Find(Cast<IViewLockOnTargetInterface>(GamePlayerCameraManager->GetViewLockTarget())) };
	if (!PotentialLockOnTargets.IsValidIndex(CurrentTargetIndex))
	{
		return;
	}

	// Move through the target array from the current target index in input direction and lock on to target in direction
	LockView(Cast<AActor>(PotentialLockOnTargets[FMath::Clamp(CurrentTargetIndex + StaticCast<int32>(FMath::Sign(InputValue)), 0, PotentialLockOnTargets.Num() - 1)]));
}

void UPlayerViewLockOnComponent::SetGamePlayerCameraManager(TObjectPtr<AGamePlayerCameraManager> InGamePlayerCameraManager)
{
	GamePlayerCameraManager = InGamePlayerCameraManager;
}

void UPlayerViewLockOnComponent::GetPotentialLockOnTargets(TObjectPtr<APlayerController> PlayerController, const FVector& ViewWorldLocation,
	TArray<IViewLockOnTargetInterface*>& OutPotentialTargets)
{
	OutPotentialTargets.Empty();

	// Find actors inside camera view frustum
	const TObjectPtr<ULocalPlayer> LocalPlayer = PlayerController->GetLocalPlayer();

	if (!IsValid(LocalPlayer))
	{
		return;
	}

	const TObjectPtr<UGameViewportClient> ViewportClient = LocalPlayer->ViewportClient;
	if (!IsValid(ViewportClient))
	{
		return;
	}

	// Get scene view structure
	FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(ViewportClient->Viewport,
		World->Scene,
		ViewportClient->EngineShowFlags).SetRealtimeUpdate(true));

	FVector ViewLocation;
	FRotator ViewRotation;
	FSceneView* SceneView{ LocalPlayer->CalcSceneView(&ViewFamily, ViewLocation, ViewRotation, ViewportClient->Viewport) };

	if (SceneView == nullptr)
	{
		return;
	}

	// Get actors around view
	TArray<FHitResult> Hits;
	if (!World->SweepMultiByChannel(Hits, ViewWorldLocation, ViewWorldLocation, FQuat::Identity, ECollisionChannel::ECC_Camera, FCollisionShape::MakeSphere(10000.0f)))
	{
		return;
	}

	for (const FHitResult& Hit : Hits)
	{
		const TObjectPtr<AActor> Actor{ Hit.GetActor() };

		// Ignore the player character actor as the player character can never be locked on to with the view
		if (PlayerController->GetPawn() == Actor)
		{
			continue;
		}

		// Does the actor implement the view lock on target interface, making it a valid lock on target?
		IViewLockOnTargetInterface* const ViewLockOnTargetInterface = Cast<IViewLockOnTargetInterface>(Actor);

		if (ViewLockOnTargetInterface == nullptr)
		{
			continue;
		}

		// Is the actor beyond the Z depth lock on limit
		FVector ScreenLocation;
		PlayerController->ProjectWorldLocationToScreenWithDistance(Actor->GetActorLocation(), ScreenLocation);
		if (ScreenLocation.Z > StaticCast<double>(ViewLockMaxDepth))
		{
			continue;
		}

		// Can the actor currently be considered as a view lock on target
		if (!IViewLockOnTargetInterface::Execute_IsConsideredForViewLockOn(Actor))
		{
			continue;
		}

		// Calculate the actor's bounds
		FVector ActorBoundsOrigin;
		FVector ActorBoundsExtent;
		Actor->GetActorBounds(false, ActorBoundsOrigin, ActorBoundsExtent, true);

		// Is the actor inside the scene view's frustum
		const bool ActorInView{ SceneView->ViewFrustum.IntersectBox(ActorBoundsOrigin, ActorBoundsExtent) };
		if (!ActorInView)
		{
			continue;
		}

		// Actor is valid lock on target. Add it to the array of potential targets
		OutPotentialTargets.Add(ViewLockOnTargetInterface);
	}
}

void UPlayerViewLockOnComponent::CheckOverMaxDepth()
{
	if ((GamePlayerCameraManager->GetViewLockTarget()->GetActorLocation() - GamePlayerCameraManager->GetViewWorldLocation()).Length() > ViewLockMaxDepth)
	{
		UnlockView();
	}
}

void UPlayerViewLockOnComponent::LockView(TObjectPtr<AActor> Target)
{
	GamePlayerCameraManager->LockViewToTarget(Target);

	if (!World->GetTimerManager().IsTimerActive(OverMaxDepthCheckTimerHandle))
	{
		World->GetTimerManager().SetTimer(OverMaxDepthCheckTimerHandle, this, &UPlayerViewLockOnComponent::CheckOverMaxDepth, OverMaxDepthCheckIntervalSeconds, true);
	}
}

void UPlayerViewLockOnComponent::UnlockView()
{
	GamePlayerCameraManager->ClearViewLockTarget();
	World->GetTimerManager().ClearTimer(OverMaxDepthCheckTimerHandle);
}
