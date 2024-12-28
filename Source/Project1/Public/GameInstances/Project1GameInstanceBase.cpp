// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1GameInstanceBase.h"
#include "ProjectInput/InputKeyStateManager.h"

UProject1GameInstanceBase::UProject1GameInstanceBase()
{
	InputKeyStateManager = CreateDefaultSubobject<UInputKeyStateManager>(FName(TEXT("InputKeyStateManager")));
}
