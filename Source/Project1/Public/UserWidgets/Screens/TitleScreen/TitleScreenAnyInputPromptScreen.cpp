// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleScreenAnyInputPromptScreen.h"
#include "ProjectInput/UserInterfaceInput/UIInputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "HUDs/Project1HUDBase.h"

void UTitleScreenAnyInputPromptScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ProjectHUD = CastChecked<AProject1HUDBase>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());
}

void UTitleScreenAnyInputPromptScreen::SetupUIInputActionEvents()
{
	BindUIInputActionEvent(AnyInputUIInputAction, this, &UTitleScreenAnyInputPromptScreen::OnAnyInputUIInput);
}

void UTitleScreenAnyInputPromptScreen::NativeOnShown()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("AnyInputPromptScreen: Shown")));
}

void UTitleScreenAnyInputPromptScreen::OnAnyInputUIInput(const FUIInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, FString::Printf(TEXT("TitleScreen AnyInputPromptScreen OnAnyInputUIInput called with value: %s"),
		*Value.Get<FVector2D>().ToString()));

	// Push main menu widget onto screen if the input was pressed
	// TODO: Add triggers to UI input actions/mapping so that do not need to keep checking if the key was pressed/released in code
	if (Value.Get<float>() > 0.0)
	{
		ProjectHUD->PushContentToPrimaryLayoutLayer(TitleScreenMainMenuScreenPrimaryLayoutLayerName, TitleScreenMainMenuScreenClass);
	}
}
