// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Project1HUDBase.generated.h"

class UPrimaryLayoutUserWidgetBase;
class UUIInputActionMapping;
struct FGameplayTag;
class UScreenUserWidgetBase;
class ULayerUserWidgetBase;

/**
 * 
 */
UCLASS()
class PROJECT1_API AProject1HUDBase : public AHUD
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "UI Input Action Mapping Asset"))
	TObjectPtr<UUIInputActionMapping> UIInputActionMapping{ nullptr };

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPrimaryLayoutUserWidgetBase> PrimaryLayoutWidgetClass{ nullptr };

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPrimaryLayoutUserWidgetBase> PrimaryLayoutWidget{ nullptr };

public:
	void PushContentToPrimaryLayoutLayer(const FGameplayTag& LayerName, const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass);
	void PopContentFromPrimaryLayoutLayer(const FGameplayTag& LayerName);
	ULayerUserWidgetBase* GetRegisteredPrimaryLayoutLayer(const FGameplayTag& LayerName);
	void SetActiveInputPrimaryLayoutLayer(const FGameplayTag& LayerName);

	FORCEINLINE TObjectPtr<const UUIInputActionMapping> GetUIInputActionMapping() const { return UIInputActionMapping; }

private:
	void BeginPlay() override;
};
