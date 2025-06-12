// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactions/InteractionBase.h"
#include "SinglePressInteraction.generated.h"

/**
 * 
 */
UCLASS()
class USinglePressInteraction : public UInteractionBase
{
	GENERATED_BODY()
	
public:
	virtual void OnInteractInputPressed() override;
};
