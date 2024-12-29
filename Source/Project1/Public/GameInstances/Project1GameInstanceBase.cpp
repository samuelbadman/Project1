// Fill out your copyright notice in the Description page of Project Settings.


#include "Project1GameInstanceBase.h"
#include "ProjectInput/InputKeyStateController.h"

UProject1GameInstanceBase::UProject1GameInstanceBase()
{
	InputKeyStateController = CreateDefaultSubobject<UInputKeyStateController>(FName(TEXT("InputKeyStateController")));
}
