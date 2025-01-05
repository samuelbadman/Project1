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
class UProject1GameInstanceBase;

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

	TObjectPtr<UProject1GameInstanceBase> Project1GameInstance{ nullptr };

public:
	void PushContentToPrimaryLayoutLayer(const FGameplayTag& LayerName, const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass);
	void PopContentFromPrimaryLayoutLayer(const FGameplayTag& LayerName);
	ULayerUserWidgetBase* GetRegisteredPrimaryLayoutLayer(const FGameplayTag& LayerName);
	void SetActiveInputPrimaryLayoutLayer(const FGameplayTag& LayerName);
	const FGameplayTag& GetActiveInputPrimaryLayoutLayerName() const;
	bool IsContentOnTopOfPrimaryLayoutLayer(const FGameplayTag& LayerName, TObjectPtr<UScreenUserWidgetBase> Widget) const;

	FORCEINLINE TObjectPtr<const UUIInputActionMapping> GetUIInputActionMapping() const { return UIInputActionMapping; }

private:
	void BeginPlay() override;

	void ControllerAnyKeyInputBinding(const FKey& Key, const EInputEvent Event);
};
