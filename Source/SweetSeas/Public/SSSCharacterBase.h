// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CoreAttributeSet.h"
#include "SSSCharacterBase.generated.h"

UCLASS()
class SWEETSEAS_API ASSSCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASSSCharacterBase();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual class UCoreAttributeSet* GetAttributeSetBase() const;

	UPROPERTY()
	class UCoreAttributeSet* AttributeSetBase;

	UFUNCTION(BlueprintCallable, Category = "GASDocumentation|GDCharacter|Attributes")
	int32 GetCharacterLevel() const;

	// Gets the Current value of MoveSpeed
	UFUNCTION(BlueprintCallable, Category = "GASDocumentation|GDCharacter|Attributes")
	float GetMoveSpeed() const;


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void InitializeAttributes();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TWeakObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;
//	TWeakObjectPtr<class UCoreAttributeSet> AttributeSetBase;

	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASDocumentation|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;
};
