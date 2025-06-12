// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1GameplayLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Interactions/SinglePressInteraction.h" 
#include "Interactions/HoldInteraction.h" 
#include "Interactions/TapInteraction.h" 
#include "Enumerations/InteractionType.h"

bool UProject1GameplayLibrary::IsActorPlayerCharacter(UObject* WorldContextObject, AActor* Actor)
{
	return (Actor == StaticCast<AActor*>(UGameplayStatics::GetPlayerCharacter(WorldContextObject, 0)));
}

UInteractionBase* UProject1GameplayLibrary::CreateInteraction(EInteractionType InteractionType, UObject* Outer)
{
	switch (InteractionType)
	{
	case EInteractionType::SinglePress: return NewObject<USinglePressInteraction>(Outer);
	case EInteractionType::Hold: return NewObject<UHoldInteraction>(Outer);
	case EInteractionType::Tap: return NewObject<UTapInteraction>(Outer);
	default: return nullptr;
	}
}
