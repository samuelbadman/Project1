// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1AnimNotifyBase.h"

void UProject1AnimNotifyBase::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
}
