// Fill out your copyright notice in the Description page of Project Settings.


#include "SSSCharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "SSSCharacterBase.h"


USSSCharacterMovementComponent::USSSCharacterMovementComponent() {

}

float USSSCharacterMovementComponent::GetMaxSpeed() const
{
	ASSSCharacterBase* Owner = Cast<ASSSCharacterBase>(GetOwner());
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() No Owner"), *FString(__FUNCTION__));
		return Super::GetMaxSpeed();
	}

	return Owner->GetMoveSpeed();

}