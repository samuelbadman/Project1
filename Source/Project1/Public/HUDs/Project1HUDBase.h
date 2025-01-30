// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Project1HUDBase.generated.h"

class UPrimaryLayoutUserWidgetBase;
struct FGameplayTag;
class UScreenUserWidgetBase;
class ULayerUserWidgetBase;
class UProject1GameViewportClientBase;
class UScreenWidgetLoadPayloadBase;
class FConfirmModalOptionSelectedDelegate;

/**
 *
 */
UCLASS()
class PROJECT1_API AProject1HUDBase : public AHUD
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "PrimaryWidgetLayout")
	TSubclassOf<UPrimaryLayoutUserWidgetBase> PrimaryLayoutWidgetClass{ nullptr };

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPrimaryLayoutUserWidgetBase> PrimaryLayoutWidget{ nullptr };

public:
	UFUNCTION(BlueprintCallable)
	void PushContentToPrimaryLayoutWidgetLayer(
		const FGameplayTag& LayerName,
		const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass,
		UScreenWidgetLoadPayloadBase* const LoadPayloadObject = nullptr
	);

	UFUNCTION(BlueprintCallable)
	void PopContentFromPrimaryLayoutWidgetLayer(const FGameplayTag& LayerName);

	UFUNCTION(BlueprintCallable)
	ULayerUserWidgetBase* GetRegisteredPrimaryLayoutWidgetLayer(const FGameplayTag& LayerName) const;

	UFUNCTION(BlueprintCallable)
	bool DoesPrimaryLayoutWidgetLayerBlockContentInput(const int32 ContentLayerPriority) const;

	UFUNCTION(BlueprintCallable)
	bool IsPrimaryLayoutWidgetLayerEmpty(const FGameplayTag& LayerName) const;

	// Helper function to setup and push a confirm modal to a widget layer
	UFUNCTION(BlueprintCallable)
	void PushConfirmModalToWidgetLayer(
		const FGameplayTag& LayerName,
		const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass,
		const FText ModalPromptText,
		const FText Option1Text,
		const FText Option2Text,
		const FConfirmModalOptionSelectedDelegate& Option1SelectedDelegate,
		const FConfirmModalOptionSelectedDelegate& Option2SelectedDelegate
	);

	// Helper function to setup and push a dynamic modal to a widget layer
	UFUNCTION(BlueprintCallable)
	void PushDynamicModalToWidgetLayer(
		const FGameplayTag& LayerName,
		const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass,
		const FText ModalPromptText,
		const TArray<FDynamicModalOptionData>& Options
	);

protected:
	void BeginPlay() override;
};
