// Fill out your copyright notice in the Description page of Project Settings.


#include "BinarySettingWidget.h"

ESettingInputResult UBinarySettingWidget::ProcessConfirmInput()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, FString::Printf(TEXT("%s handled confirm input"), *GetName()));
	return ESettingInputResult::Handled;
}
