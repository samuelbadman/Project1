// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Project1AnimNotifyBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UProject1AnimNotifyBase : public UAnimNotify
{
	GENERATED_BODY()

protected:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
