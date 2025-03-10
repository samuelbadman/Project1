// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project1AnimInstanceBase.h"
#include "MannySimpleAnimInstance.generated.h"

class AProject1CharacterBase;

/**
 *
 */
UCLASS()
class PROJECT1_API UMannySimpleAnimInstance : public UProject1AnimInstanceBase
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, Category = "AnimationData", meta = (AllowPrivateAccess = "true"))
	bool bIsMoving;

	TObjectPtr<AProject1CharacterBase> ProjectCharacterOwner;

	FVector CharacterOwnerVelocity;

public:
	UMannySimpleAnimInstance();

private:
	//// Native initialization override point
	void NativeInitializeAnimation() override;
	//// Native update override point. It is usually a good idea to simply gather data in this step and 
	//// for the bulk of the work to be done in NativeThreadSafeUpdateAnimation.
	void NativeUpdateAnimation(float DeltaSeconds) override;
	//// Native thread safe update override point. Executed on a worker thread just prior to graph update 
	//// for linked anim instances, only called when the hosting node(s) are relevant
	void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	//// Native Post Evaluate override point
	//void NativePostEvaluateAnimation() override;
	//// Native Uninitialize override point
	//void NativeUninitializeAnimation() override;
};
