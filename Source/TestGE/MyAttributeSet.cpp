// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttributeSet.h"

#include "AbilitySystemGlobals.h"
#include "GameplayEffectExtension.h"
#include "MyCharacter.h"

UMyAttributeSet::UMyAttributeSet()
{
}

/*
float UMyAttributeSet::GetCriticalChance()
{
	const AMyCharacter* TargetCharacter = Cast<AMyCharacter>(GetOuter());
	if(TargetCharacter)
	{
		if(TargetCharacter->TestType == ETestType::PostAttriteChange)
		{
			const bool IsAddCriticalChanceByRage = GetOwningAbilitySystemComponent()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Effect.AddCriticalChanceByRage")));
			if(IsAddCriticalChanceByRage)
			{
				const float CurVal = GetRage();
				const float Mod = CurVal * 0.2f;
				return CriticalChance.GetCurrentValue() + Mod;
			}
		}
	}
	return CriticalChance.GetCurrentValue();
}*/

void UMyAttributeSet::Init()
{
	// Listen to Effect Apply
	AMyCharacter* TargetCharacter = Cast<AMyCharacter>(GetOwningActor());
	if(TargetCharacter && TargetCharacter->TestType == ETestType::PostAttributeChange)
	{
		GetOwningAbilitySystemComponent()->OnGameplayEffectAppliedDelegateToTarget.AddUObject(this, &UMyAttributeSet::OnApplyGameplayEffectCallback);
	}
}

UWorld* UMyAttributeSet::GetWorld() const
{
	const UObject* Outer = GetOuter();
	check(Outer);

	return Outer->GetWorld();
}

void UMyAttributeSet::OnApplyGameplayEffectCallback(UAbilitySystemComponent* Target,
	const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle)
{
	// When the Effect(Per Rage Add 0.2 CriticalChance) applied, Modify the CriticalChance
	FGameplayTagContainer AllAssetTags;
	SpecApplied.GetAllAssetTags(AllAssetTags);
	if(AllAssetTags.HasTag(FGameplayTag::RequestGameplayTag(FName("Effect.PostAttributeChange"))))
	{
		const float Mod = GetRage() * 0.2f;
		const float NewCriticalChance = GetCriticalChance() + Mod;
		SetCriticalChance(NewCriticalChance);

		Handle = ActiveHandle;

		// Listen to Effect Remove
		FOnActiveGameplayEffectRemoved_Info* DelPtr = GetOwningAbilitySystemComponent()->OnGameplayEffectRemoved_InfoDelegate(Handle);
		if (DelPtr)
		{
			DelPtr->AddUObject(this, &UMyAttributeSet::OnGameplayEffectRemoved);
		}
	}
}

void UMyAttributeSet::OnGameplayEffectRemoved(const FGameplayEffectRemovalInfo& InGameplayEffectRemovalInfo)
{
	const float CurrentRage = GetRage();
	const float NewCriticalChance = FMath::Max(0,GetCriticalChance() - CurrentRage * 0.2f);
	SetCriticalChance(NewCriticalChance);
}

bool UMyAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if(Data.EvaluatedData.Attribute == GetRageAttribute())
	{
		SetRage(FMath::Max(GetRage(), 0.0f));
	}
	else if(Data.EvaluatedData.Attribute == GetCriticalChanceAttribute())
	{
		/*
		 * When using the AttributeBase approach,
		 * calling SetCriticalChance() here will cause other GE's to modify CriticalChance incorrectly
		 */
		//SetCriticalChance(FMath::Max(GetCriticalChance(), 0.0f));
	}
}

void UMyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UMyAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	if(Attribute == GetRageAttribute())
	{
		AMyCharacter* TargetCharacter = Cast<AMyCharacter>(GetOwningActor());
		if(TargetCharacter && TargetCharacter->TestType == ETestType::PostAttributeChange)
		{
			const bool IsAddCriticalChanceByRage = GetOwningAbilitySystemComponent()->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Effect.PostAttributeChange")));
			if(IsAddCriticalChanceByRage)
			{
				//const float CurVal = GetRage();
				//const float Mod = CurVal * 0.2f;
				//GetOwningAbilitySystemComponent()->ApplyModToAttribute(UMyAttributeSet::GetCriticalChanceAttribute(), EGameplayModOp::Additive, Mod);

				const float Diff = NewValue - OldValue;
				const float Mod = Diff * 0.2f;
				const float NewCriticalChance = GetCriticalChance() + Mod;
				SetCriticalChance(NewCriticalChance);
			}
		}
	}
}

void UMyAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
}

void UMyAttributeSet::OnAttributeAggregatorCreated(const FGameplayAttribute& Attribute,
	FAggregator* NewAggregator) const
{
	Super::OnAttributeAggregatorCreated(Attribute, NewAggregator);
}
