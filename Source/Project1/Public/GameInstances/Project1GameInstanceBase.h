// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "Project1GameInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UProject1GameInstanceBase : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	bool TestSetting1Value = true;

	UPROPERTY(BlueprintReadWrite)
	bool TestSetting2Value = false;

	UPROPERTY(BlueprintReadWrite)
	bool TestSetting3Value = false;

	UPROPERTY(BlueprintReadWrite)
	FString TestSettingValue4{ "Value3" };

private:
	FStreamableManager StreamableManager{};

public:
	void Init() override;

	FORCEINLINE FStreamableManager& GetStreamableManager() { return StreamableManager; }
};
