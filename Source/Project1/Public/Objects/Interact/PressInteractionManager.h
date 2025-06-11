// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionManagerBase.h"
#include "PressInteractionManager.generated.h"

/**
 * 
 */
UCLASS()
class UPressInteractionManager : public UInteractionManagerBase
{
	GENERATED_BODY()
	
public:
	virtual void StartInteraction(const TObjectPtr<AActor> Interactable, const TObjectPtr<AActor> Interactor) override;
};
