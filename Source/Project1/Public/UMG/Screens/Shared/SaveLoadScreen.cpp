// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadScreen.h"
#include "Objects/ScreenLoadPayloads/SaveLoadScreenLoadPayload.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/PlayerControllers/Project1PlayerControllerBase.h"
#include "Components/ActorComponents/UIInputComponent.h"
#include "Objects/UIInput/Inputs/SaveLoadScreenUIInput.h"
#include "InputActionValue.h"
#include "Objects/UserWidgetComponents/ButtonMenuComponent.h"
#include "GameInstances/Project1GameInstanceBase.h"
#include "SaveGame/SaveManager.h"
#include "SaveGame/SaveGameObjects/MetaSaveGame.h"
#include "SaveGame/SaveDataStructures/SaveSlotSaveData.h"
#include "UMG/Components/SaveLoad/SaveSlotWidget.h"
#include "Components/Spacer.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ScrollBox.h"
#include "UMG/Components/Buttons/Project1ButtonBase.h"

USaveLoadScreen::USaveLoadScreen()
	:
	ButtonMenuComponent(CreateDefaultSubobject<UButtonMenuComponent>(FName(TEXT("ButtonMenuComponent")))),
	UIInputKey({}),
	SaveSlotWidgetClass(nullptr),
	SaveSlotSpacing({}),
	bInSaveMode(true),
	SaveLoadScreenUIInput(nullptr),
	CancelInputDelegateHandle({}),
	ConfirmInputDelegateHandle({}),
	NavigateInputDelegateHandle({})
{
}

TArray<USaveSlotWidget*> USaveLoadScreen::CreateExistingSaveSlotWidgets()
{
	// Get array of save slot data saved inside the meta save game. The meta save game is loaded when the game is opened if it exists
	const TArray<FSaveSlotSaveData>& SaveSlotSaveData{
		CastChecked<UProject1GameInstanceBase>(UGameplayStatics::GetGameInstance(this))->GetSaveManager()->GetMetaSaveGameObject()->GameSaveSlots };

	// If there is no saved save slot data, there are no existing save slots to create
	if (SaveSlotSaveData.IsEmpty())
	{
		return TArray<USaveSlotWidget*>{};
	}

	// Load save slot widget class asset from disk
	// Cannot create existing save slot widgets if the save slot widget class failed to load. Was a class set in the derived blueprint property?
	const TObjectPtr<UClass> LoadedSaveSlotWidgetClass{ SaveSlotWidgetClass.LoadSynchronous() };

	// Get the save slot widget parent container widget
	const TObjectPtr<UVerticalBox> SaveSlotWidgetParent{ GetSaveSlotWidgetContainer() };

	// Cannot create save slot widgets without a valid parent widget. If this fails, did you remember to implement GetSaveSlotWidgetContainer() in the derived blueprint?
	check(IsValid(SaveSlotWidgetParent));

	// Initialize result array
	TArray<USaveSlotWidget*> Result{};
	Result.Reserve(SaveSlotSaveData.Num());

	// For each save slot data in the saved save slot save data
	for (const FSaveSlotSaveData& SaveSlotData : SaveSlotSaveData)
	{
		// Create a save slot widget for the save slot data. Add save slot widget to parent container widget
		const TObjectPtr<USaveSlotWidget> SaveSlotWidget{ CreateAndAddSaveSlotWidget(SaveSlotWidgetParent, LoadedSaveSlotWidgetClass) };

		// Set data for save slot widget
		SaveSlotWidget->SetSaveSlotDataId(SaveSlotData.Id);

		// Bind function to save slot selected delegate
		SaveSlotWidget->OnSaveSlotSelectedDelegate.AddDynamic(this, &USaveLoadScreen::OnSaveSlotSelected);

		// Add new save slot widget to result array
		Result.Add(SaveSlotWidget);
	}

	return Result;
}

USaveSlotWidget* USaveLoadScreen::CreateNewSaveSlotDataAndWidget()
{
	// Create new save slot widget and add it to the save slot container widget
	const TObjectPtr<USaveSlotWidget> SaveSlotWidget{ CreateAndAddSaveSlotWidget(GetSaveSlotWidgetContainer(), SaveSlotWidgetClass.LoadSynchronous()) };

	// Create a new save slot data within the save manager for the save slot widget and set the widget's unique id to the id value returned from the save manager
	SaveSlotWidget->SetSaveSlotDataId(CastChecked<UProject1GameInstanceBase>(UGameplayStatics::GetGameInstance(this))->GetSaveManager()->CreateNewSaveSlot());

	// Return the new save slot widget
	return SaveSlotWidget;
}

void USaveLoadScreen::CloseScreen()
{
	// TODO: This could be a function in the screen widget parent class for all screens to use
	CastChecked<AProject1HUDBase>(PlayerController->GetHUD())->PopContentFromPrimaryLayoutWidgetLayer(GetOwningLayerName());
}

void USaveLoadScreen::NativeConsumeLoadPayload(TObjectPtr<UScreenWidgetLoadPayloadBase> LoadPayload)
{
	Super::NativeConsumeLoadPayload(LoadPayload);

	const TObjectPtr<USaveLoadScreenLoadPayload> Payload{ Cast<USaveLoadScreenLoadPayload>(LoadPayload) };
	bInSaveMode = Payload->bSaving;
}

void USaveLoadScreen::NativeOnPushedToLayerStack()
{
	Super::NativeOnPushedToLayerStack();

	PlayerController = CastChecked<AProject1PlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	SaveLoadScreenUIInput = PlayerController->GetUIInputComponent()->GetUIInputAs<USaveLoadScreenUIInput>(UIInputKey);

	// Bind to UI input delegate events
	CancelInputDelegateHandle = SaveLoadScreenUIInput->OnCancelInputTriggeredDelegate.AddUObject(this, &USaveLoadScreen::OnCancelInputTriggered);
	ConfirmInputDelegateHandle = SaveLoadScreenUIInput->OnConfirmInputTriggeredDelegate.AddUObject(this, &USaveLoadScreen::OnConfirmInputTriggered);
	NavigateInputDelegateHandle = SaveLoadScreenUIInput->OnNavigateInputTriggeredDelegate.AddUObject(this, &USaveLoadScreen::OnNavigateInputTriggered);

	SaveLoadScreenUIInput->Add(PlayerController->GetEnhancedInputLocalPlayerSubsystem());
}

void USaveLoadScreen::NativeOnPoppedFromLayerStack()
{
	SaveLoadScreenUIInput->OnCancelInputTriggeredDelegate.Remove(CancelInputDelegateHandle);
	CancelInputDelegateHandle.Reset();

	SaveLoadScreenUIInput->OnConfirmInputTriggeredDelegate.Remove(ConfirmInputDelegateHandle);
	ConfirmInputDelegateHandle.Reset();

	SaveLoadScreenUIInput->OnNavigateInputTriggeredDelegate.Remove(NavigateInputDelegateHandle);
	NavigateInputDelegateHandle.Reset();

	SaveLoadScreenUIInput->Remove(PlayerController->GetEnhancedInputLocalPlayerSubsystem());
}

void USaveLoadScreen::OnCancelInputTriggered(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		CloseScreen();
	}
}

void USaveLoadScreen::OnConfirmInputTriggered(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		ButtonMenuComponent->PressFocusedButton();
	}
}

void USaveLoadScreen::OnNavigateInputTriggered(const FInputActionValue& Value)
{
	if (CanReceiveInput())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Save load screen Navigate input triggered: %s"), *Value.Get<FVector2D>().ToString()));

		// The button menu is laid out in the widget vertically so, use the Y input axis to navigate the button menu
		const TObjectPtr<UProject1ButtonBase> NavigatedButton{ ButtonMenuComponent->NavigateMenu(-Value.Get<FVector2D>().Y, true) };
		if (IsValid(NavigatedButton))
		{
			GetSaveSlotWidgetScrollBox()->ScrollWidgetIntoView(NavigatedButton);
		}
	}
}

TObjectPtr<USaveSlotWidget> USaveLoadScreen::CreateAndAddSaveSlotWidget(TObjectPtr<UVerticalBox> SaveSlotWidgetContainerWidget,	TObjectPtr<UClass> LoadedSaveSlotWidgetClass)
{
	// Construct a spacer widget and add it to the save slot parent container widget
	// Set the spacer widget's spacing
	const TObjectPtr<USpacer> Spacer{ WidgetTree->ConstructWidget<USpacer>() };
	const TObjectPtr<UVerticalBoxSlot> SpacerVBoxSlot{ CastChecked<UVerticalBoxSlot>(SaveSlotWidgetContainerWidget->AddChild(Spacer)) };
	SpacerVBoxSlot->SetPadding(SaveSlotSpacing);

	// Create a save slot widget for the save slot data. Add save slot widget to parent container widget
	const TObjectPtr<USaveSlotWidget> SaveSlotWidget{ CreateWidget<USaveSlotWidget>(PlayerController, LoadedSaveSlotWidgetClass) };
	SaveSlotWidgetContainerWidget->AddChild(SaveSlotWidget);

	return SaveSlotWidget;
}

void USaveLoadScreen::OnSaveSlotSelected(USaveSlotWidget* SaveSlot)
{
	// Get the save manager object
	const TObjectPtr<USaveManager> SaveManager{ CastChecked<UProject1GameInstanceBase>(UGameplayStatics::GetGameInstance(this))->GetSaveManager() };

	// Get the selected slot's unique name as a string
	const FString SaveSlotName{ SaveSlot->GetUniqueSaveSlotName().ToString() };

	// If in save mode
	if (bInSaveMode)
	{
		SaveManager->SaveGame(SaveSlotName, false);
		// TODO: Play sound/show notification to inform the player the game has been saved
		CloseScreen();
	}
	else
	{
		SaveManager->LoadGame(SaveSlotName, false);
	}
}
