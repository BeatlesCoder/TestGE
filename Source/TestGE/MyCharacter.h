// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UENUM(BlueprintType)
enum class ETestType : uint8
{
	AttributeBase,
	GMMC,
	GEEC,
	OverrideGetter,
	PostAttributeChange,
};

UCLASS(PrioritizeCategories=0)
class TESTGE_API AMyCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	UFUNCTION(BlueprintCallable, Category="AMyCharacter")
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AMyCharacter")
	ETestType TestType;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void PossessedBy(AController* NewController) override;

	virtual void InitializeAttributes();

	virtual void AddStartupEffects();

	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AMyCharacter|Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;
	
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(Transient)
	class UMyAttributeSet* MyAttributeSet;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "AMyCharacter|Camera")
	class USpringArmComponent* ThirdPersonCameraBoom;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "AMyCharacter|Camera")
	class UCameraComponent* ThirdPersonCamera;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AMyCharacter|Camera")
	float BaseTurnRate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AMyCharacter|Camera")
	float BaseLookUpRate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AMyCharacter|UI")
	TSubclassOf<class UMyUserWidget> UIHUDWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "AMyCharacter|UI")
	class UMyUserWidget* UIHUDWidget;
	
	UFUNCTION()
	void CreateHUD();
	
	// Mouse
	void LookUp(float Value);

	// Gamepad
	void LookUpRate(float Value);

	// Mouse
	void Turn(float Value);

	// Gamepad
	void TurnRate(float Value);

	// Mouse + Gamepad
	void MoveForward(float Value);

	// Mouse + Gamepad
	void MoveRight(float Value);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
