// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Test_Idle.h"

UBTTask_Test_Idle::UBTTask_Test_Idle()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Test_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}

void UBTTask_Test_Idle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}
