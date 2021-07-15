// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreAttributeSet.h"
#include "Net/UnrealNetwork.h"

UCoreAttributeSet::UCoreAttributeSet() {

}

void UCoreAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCoreAttributeSet, MoveSpeed, COND_None, REPNOTIFY_Always);
}

void UCoreAttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCoreAttributeSet, MoveSpeed, OldMoveSpeed);
}

