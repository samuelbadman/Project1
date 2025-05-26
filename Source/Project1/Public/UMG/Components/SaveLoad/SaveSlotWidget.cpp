// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSlotWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstances/Project1GameInstanceBase.h"
#include "SaveGame/SaveManager.h"

FName USaveSlotWidget::GetUniqueSaveSlotName() const
{
	const FSaveSlot* const SaveSlot{ CastChecked<UProject1GameInstanceBase>(UGameplayStatics::GetGameInstance(this))->GetSaveManager()->GetSaveSlotData(SaveSlotDataId) };
	return (SaveSlot) ? SaveSlot->UniqueName : NAME_None;
}
