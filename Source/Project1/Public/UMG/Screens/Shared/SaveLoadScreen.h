// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG/Screens/ScreenUserWidgetBase.h"
#include "GameplayTagContainer.h"
#include "SaveLoadScreen.generated.h"

class AProject1PlayerControllerBase;
class USaveLoadScreenUIInput;
class UButtonMenuComponent;
struct FInputActionValue;
class USaveSlotWidget;
class UVerticalBox;
class USaveSlotWidget;
class UScrollBox;

/**
 * 
 */
UCLASS()
class USaveLoadScreen : public UScreenUserWidgetBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SaveLoadScreen", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UButtonMenuComponent> ButtonMenuComponent;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag UIInputKey;

	UPROPERTY(EditDefaultsOnly, Category = "SaveLoadScreen")
	TSoftClassPtr<USaveSlotWidget> SaveSlotWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "SaveLoadScreen")
	FMargin SaveSlotSpacing;

	UPROPERTY(BlueprintReadOnly, Category = "SaveLoadScreen", meta = (AllowPrivateAccess = "true"))
	bool bInSaveMode;

	TObjectPtr<AProject1PlayerControllerBase> PlayerController;
	TObjectPtr<USaveLoadScreenUIInput> SaveLoadScreenUIInput;
	FDelegateHandle CancelInputDelegateHandle;
	FDelegateHandle ConfirmInputDelegateHandle;
	FDelegateHandle NavigateInputDelegateHandle;

public:
	USaveLoadScreen();

	UFUNCTION(BlueprintImplementableEvent, Category = "SaveLoadScreen")
	UVerticalBox* GetSaveSlotWidgetContainer() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "SaveLoadScreen")
	UScrollBox* GetSaveSlotWidgetScrollBox() const;

	// Creates save slot widgets for save slots that are stored inside the meta save game and adds them as a child to the save slot 
	// widget container returned by GetSaveSlotWidgetContainer(). Returns an array of the created save slot widgets
	UFUNCTION(BlueprintCallable, Category = "SaveLoadScreen")
	TArray<USaveSlotWidget*> CreateExistingSaveSlotWidgets();

	// Creates a new save slot widget, initializes it and adds it to the save slot widget container. Returns the newly created save slot widget
	UFUNCTION(BlueprintCallable, Category = "SaveLoadScreen")
	USaveSlotWidget* CreateNewSaveSlotDataAndWidget();

	UFUNCTION(BlueprintCallable, Category = "SaveLoadScreen")
	void CloseScreen();

private:
	void NativeConsumeLoadPayload(TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayload) override;
	void NativeOnPushedToLayerStack() override;
	void NativeOnPoppedFromLayerStack() override;

	void OnCancelInputTriggered(const FInputActionValue& Value);
	void OnConfirmInputTriggered(const FInputActionValue& Value);
	void OnNavigateInputTriggered(const FInputActionValue& Value);

	// Creates a new save slot widget and adds it as a child to the passed parent widget
	TObjectPtr<USaveSlotWidget> CreateAndAddSaveSlotWidget(TObjectPtr<UVerticalBox> SaveSlotWidgetContainerWidget, TObjectPtr<UClass> LoadedSaveSlotWidgetClass);

	UFUNCTION()
	void OnSaveSlotSelected(USaveSlotWidget* SaveSlot);
};
