// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "GMMC_AddCriticalChanceByRage.generated.h"

/**
 * GMMC Test
 */
UCLASS()
class TESTGE_API UGMMC_AddCriticalChanceByRage : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UGMMC_AddCriticalChanceByRage();
	
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	UPROPERTY(Transient)
	float OldRage;
};
