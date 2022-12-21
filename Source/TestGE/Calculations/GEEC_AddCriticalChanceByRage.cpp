// Fill out your copyright notice in the Description page of Project Settings.


#include "GEEC_AddCriticalChanceByRage.h"

#include "TestGE/MyAttributeSet.h"


struct FArgAddCriticalChanceStatics
{
	FGameplayEffectAttributeCaptureDefinition RageDef;	
	FGameplayEffectAttributeCaptureDefinition CriticalChangeDef;

	FArgAddCriticalChanceStatics()
	{
		RageDef = FGameplayEffectAttributeCaptureDefinition(UMyAttributeSet::GetRageAttribute(), EGameplayEffectAttributeCaptureSource::Source, false);
		CriticalChangeDef = FGameplayEffectAttributeCaptureDefinition(UMyAttributeSet::GetCriticalChanceAttribute(), EGameplayEffectAttributeCaptureSource::Source, false);
	}
};

static FArgAddCriticalChanceStatics& ArgAddCriticalChanceStatics()
{
	static FArgAddCriticalChanceStatics Statics;
	return Statics;
}

UGEEC_AddCriticalChanceByRage::UGEEC_AddCriticalChanceByRage()
{
	RelevantAttributesToCapture.Add(ArgAddCriticalChanceStatics().RageDef);
	RelevantAttributesToCapture.Add(ArgAddCriticalChanceStatics().CriticalChangeDef);
}

void UGEEC_AddCriticalChanceByRage::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Rage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FArgAddCriticalChanceStatics().RageDef, EvaluationParameters,Rage);

	float CriticalChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FArgAddCriticalChanceStatics().CriticalChangeDef, EvaluationParameters,CriticalChance);

	if(Rage >= 0)
	{
		float Mod = Rage * 0.2f;
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UMyAttributeSet::GetCriticalChanceAttribute(), EGameplayModOp::Additive, Mod));
	}
}
