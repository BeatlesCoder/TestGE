// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEEC_AddCriticalChanceByRage.generated.h"

/**
 * GEEC Test
 * Note: GEEC can not use at Infinite GE
 */
UCLASS(BlueprintType)
class TESTGE_API UGEEC_AddCriticalChanceByRage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UGEEC_AddCriticalChanceByRage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
