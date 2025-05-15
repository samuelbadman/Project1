// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "Project1GameInstanceBase.generated.h"

class USaveManager;

/**
 * 
 */
UCLASS()
class PROJECT1_API UProject1GameInstanceBase : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// These test settings are debug values used to test setting widget functionality inside the settings screen. They are to be deleted when implementing settings screen
	UPROPERTY(BlueprintReadWrite)
	bool TestSetting1Value = true;
	UPROPERTY(BlueprintReadWrite)
	bool TestSetting2Value = false;
	UPROPERTY(BlueprintReadWrite)
	bool TestSetting3Value = false;
	UPROPERTY(BlueprintReadWrite)
	FString TestSettingValue4{ TEXT("Value3") };

private:
	UPROPERTY()
	TObjectPtr<USaveManager> SaveManager;

	FStreamableManager StreamableManager{};

public:
	UProject1GameInstanceBase();

	void Init() override;

	UFUNCTION(BlueprintCallable, Category = "GameSave")
	USaveManager* GetSaveManager() const;

	FORCEINLINE FStreamableManager& GetStreamableManager() { return StreamableManager; }
};
