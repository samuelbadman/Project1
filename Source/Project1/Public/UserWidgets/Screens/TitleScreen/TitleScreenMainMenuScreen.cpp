// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenMainMenuScreen.h"
#include "Components/UIComponents/ButtonListComponent.h"
#include "InputActionValue.h"

UTitleScreenMainMenuScreen::UTitleScreenMainMenuScreen()
{
	ButtonListComponent = CreateDefaultSubobject<UButtonListComponent>(TEXT("ButtonListComponent"));
	ButtonListComponent->SetWidgetOwner(this);
}

void UTitleScreenMainMenuScreen::NativeOnNavigateTriggered(const FInputActionValue& Value)
{
	ButtonListComponent->Navigate(StaticCast<int32>(Value.Get<FVector2D>().Y) * -1, bWrapMenuNavigation);
}

void UTitleScreenMainMenuScreen::NativeOnConfirmTriggered(const FInputActionValue& Value)
{
	ButtonListComponent->PressActiveButton();
}

void UTitleScreenMainMenuScreen::NativeOnLeftClickTriggered(const FInputActionValue& Value)
{
	ButtonListComponent->PressActiveButtonIfUnderMouse();
}
