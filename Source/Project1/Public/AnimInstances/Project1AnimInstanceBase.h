// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Pawns/Characters/Project1CharacterBase.h"
#include "Project1AnimInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UProject1AnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
	
private:
	TObjectPtr<AProject1CharacterBase> Project1CharacterOwner;

public:
	UProject1AnimInstanceBase();

protected:
	//// the below functions are the native overrides for each phase
	//// Native initialization override point
	void NativeInitializeAnimation() override;
	//// Native update override point. It is usually a good idea to simply gather data in this step and 
	//// for the bulk of the work to be done in NativeThreadSafeUpdateAnimation.
	//void NativeUpdateAnimation(float DeltaSeconds) override;
	//// Native thread safe update override point. Executed on a worker thread just prior to graph update 
	//// for linked anim instances, only called when the hosting node(s) are relevant
	//void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	//// Native Post Evaluate override point
	//void NativePostEvaluateAnimation() override;
	//// Native Uninitialize override point
	//void NativeUninitializeAnimation() override;

	FORCEINLINE TObjectPtr<AProject1CharacterBase> GetProject1CharacterOwner() const { return Project1CharacterOwner; }
};
