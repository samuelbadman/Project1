// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_Footstep.h"
#include "Pawns/Characters/Project1CharacterBase.h"

UAnimNotify_Footstep::UAnimNotify_Footstep()
	: FootBoneName(NAME_None)
{
}

void UAnimNotify_Footstep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (AProject1CharacterBase* ProjectCharacter = Cast<AProject1CharacterBase>(MeshComp->GetOwner()))
	{
		ProjectCharacter->OnFootstepNotify(FootBoneName);
	}
}
