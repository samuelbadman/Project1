// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenAnyInputPromptScreen.h"
#include "ProjectInput/UserInterfaceInput/UIInputActionValue.h"

void UTitleScreenAnyInputPromptScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ProjectHUD = CastChecked<AProject1HUDBase>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
}

void UTitleScreenAnyInputPromptScreen::SetupUIInputActionEvents()
{
	BindUIInputActionEvent(AnyInputUIInputAction, this, &UTitleScreenAnyInputPromptScreen::OnAnyInputUIInputTriggered);
}

void UTitleScreenAnyInputPromptScreen::NativeOnShown()
{
	// TODO: Play animation to fade in UI
}

void UTitleScreenAnyInputPromptScreen::OnAnyInputUIInputTriggered(const FUIInputActionValue& Value)
{
	// Push main menu widget onto screen if the input was pressed
	ProjectHUD->PushContentToPrimaryLayoutLayer(PrimaryLayoutLayerNameToAddMainMenuScreenTo, TitleScreenMainMenuScreenClass);
}
