// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTreeTaskNodes/Project1BTTaskNodeBase.h"
#include "BTTask_Test_Idle.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT1_API UBTTask_Test_Idle : public UProject1BTTaskNodeBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BTTask_Test_Idle", meta = (AllowPrivateAccess = "true"))
	float IdleDuration{ 0 };

	float TimeSum{ 0.0f };

public:
	UBTTask_Test_Idle();

private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
