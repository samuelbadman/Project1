// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project1AnimNotifyBase.h"
#include "AnimNotify_Footstep.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UAnimNotify_Footstep : public UProject1AnimNotifyBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	FName FootBoneName;

public:
	UAnimNotify_Footstep();

private:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
