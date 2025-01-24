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
	void PushContentToPrimaryLayoutWidgetLayer(
		const FGameplayTag& LayerName, 
		const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass, 
		UScreenWidgetLoadPayloadBase* const LoadPayloadObject = nullptr
	);
	void PopContentFromPrimaryLayoutWidgetLayer(const FGameplayTag& LayerName);
	TObjectPtr<ULayerUserWidgetBase> GetRegisteredPrimaryLayoutWidgetLayer(const FGameplayTag& LayerName) const;

	// Helper function to setup and push a confirm modal to a widget layer
	UFUNCTION(BlueprintCallable)
	void PushConfirmModalToWidgetLayer(
		const FGameplayTag& LayerName,
		const TSoftClassPtr<UScreenUserWidgetBase>& WidgetClass,
		const FText& ModalPromptText,
		const FText& Option1Text,
		const FText& Option2Text
	);

protected:
	void BeginPlay() override;
};
