// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTGE_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetRage(float Rage);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetCriticalChance(float CriticalChance);

	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetTestMode(ETestType TestType);
};
