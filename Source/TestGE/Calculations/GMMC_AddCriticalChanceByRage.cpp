// Fill out your copyright notice in the Description page of Project Settings.


#include "GMMC_AddCriticalChanceByRage.h"

#include "TestGE/MyAttributeSet.h"

struct FArgCriticalChanceStatics
{
	FGameplayEffectAttributeCaptureDefinition RageDef;
	//FGameplayEffectAttributeCaptureDefinition CriticalChance;
	
	FArgCriticalChanceStatics()
	{
		RageDef = FGameplayEffectAttributeCaptureDefinition(UMyAttributeSet::GetRageAttribute(), EGameplayEffectAttributeCaptureSource::Source, false);
		//CriticalChance = FGameplayEffectAttributeCaptureDefinition(UMyAttributeSet::GetCriticalChanceAttribute(), EGameplayEffectAttributeCaptureSource::Source, false);
	}
};

static FArgCriticalChanceStatics& ArgCriticalChanceStatics()
{
	static FArgCriticalChanceStatics Statics;
	return Statics;
}

UGMMC_AddCriticalChanceByRage::UGMMC_AddCriticalChanceByRage()
{
	RelevantAttributesToCapture.Add(ArgCriticalChanceStatics().RageDef);
	//RelevantAttributesToCapture.Add(ArgCriticalChanceStatics().CriticalChance);
}

float UGMMC_AddCriticalChanceByRage::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	/*
	auto effectcontext= Spec.GetEffectContext();
	auto ASC = effectcontext.GetInstigatorAbilitySystemComponent();
	if(Spec.Def->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Effect.AddCriticalChanceByRage"))))
	{
		float Rage = 0.0f;
		GetCapturedAttributeMagnitude(ArgCriticalChanceStatics().RageDef, Spec, EvaluationParameters, Rage);
        
		float CriticalChance = 0.0f;
		GetCapturedAttributeMagnitude(ArgCriticalChanceStatics().CriticalChance, Spec,EvaluationParameters, CriticalChance);
		return Rage * 0.2f;
	}*/

	float Rage = 0.0f;
	GetCapturedAttributeMagnitude(ArgCriticalChanceStatics().RageDef, Spec, EvaluationParameters, Rage);
	
	//float CriticalChance = 0.0f;
	//GetCapturedAttributeMagnitude(ArgCriticalChanceStatics().CriticalChance, Spec,EvaluationParameters, CriticalChance);
	
	float Diff = Rage - OldRage;
	float NewCriticalChance = Diff * 0.2f;
	return NewCriticalChance;
}
