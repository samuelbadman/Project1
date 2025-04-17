// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project1AnimInstanceBase.h"
#include "PrototypeMaleCharacterAnimInst.generated.h"

/**
 *
 */
UCLASS()
class UPrototypeMaleCharacterAnimInst : public UProject1AnimInstanceBase
{
	GENERATED_BODY()

private:
	UPROPERTY(BlueprintReadOnly, Category = "AnimData", meta = (AllowPrivateAccess = "true"))
	bool bIsMoving;

	TObjectPtr<APawn> PawnOwner;

public:
	UPrototypeMaleCharacterAnimInst();

private:
	// Native initialization override point
	void NativeInitializeAnimation() override;
	// Native update override point. It is usually a good idea to simply gather data in this step and 
	// for the bulk of the work to be done in NativeThreadSafeUpdateAnimation.
	void NativeUpdateAnimation(float DeltaSeconds) override;
	// Native thread safe update override point. Executed on a worker thread just prior to graph update 
	// for linked anim instances, only called when the hosting node(s) are relevant
	//void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	// Native Post Evaluate override point
	//void NativePostEvaluateAnimation() override;
	// Native Uninitialize override point
	//void NativeUninitializeAnimation() override;
};
