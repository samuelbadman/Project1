// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingsPageWidget.h"

void USettingsPageWidget::Show()
{
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void USettingsPageWidget::Collapse()
{
	SetVisibility(ESlateVisibility::Collapsed);
}
