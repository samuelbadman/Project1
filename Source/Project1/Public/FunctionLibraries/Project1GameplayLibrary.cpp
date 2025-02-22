// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1GameplayLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

bool UProject1GameplayLibrary::IsPlayerCharacter(UObject* WorldContextObject, AActor* Actor)
{
	return (Actor == StaticCast<AActor*>(UGameplayStatics::GetPlayerCharacter(WorldContextObject, 0)));
}
