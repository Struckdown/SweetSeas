// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SSSCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SWEETSEAS_API USSSCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	USSSCharacterMovementComponent();

	virtual float GetMaxSpeed() const override;
};
