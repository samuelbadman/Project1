// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenMasterUserWidget.h"
#include "ProjectInput/WidgetInputComponent.h"

UTitleScreenMasterUserWidget::UTitleScreenMasterUserWidget()
{
	WidgetInputComponent = CreateDefaultSubobject<UWidgetInputComponent>(FName(TEXT("WidgetInputComponent")));
}

void UTitleScreenMasterUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	WidgetInputComponent->Initialize();
}
