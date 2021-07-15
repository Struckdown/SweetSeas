// Fill out your copyright notice in the Description page of Project Settings.


#include "SSSCharacterBase.h"
#include "CoreAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/PlayerState.h"

// Sets default values
ASSSCharacterBase::ASSSCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AttributeSetBase = CreateDefaultSubobject<UCoreAttributeSet>(TEXT("AttributeSetBase"));

}

UAbilitySystemComponent* ASSSCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

UCoreAttributeSet* ASSSCharacterBase::GetAttributeSetBase() const
{
	return AttributeSetBase;
}

// Called when the game starts or when spawned
void ASSSCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASSSCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASSSCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ASSSCharacterBase::GetMoveSpeed() const
{
	if (AttributeSetBase)
	{
		AttributeSetBase->GetMoveSpeed();
	}

	return 0.0f;
}

void ASSSCharacterBase::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);
	APlayerState* PS = GetPlayerState<APlayerState>();

	if (PS) {
		// Set the ASC on the Server. Clients do this in OnRep_PlayerState()
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
	
		// AI won't have PlayerControllers so we can init again here just to be sure. No harm in initing twice for heroes that have PlayerControllers.
		//PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

		// Set the AttributeSetBase for convenience attribute functions
		//AttributeSetBase = PS->GetAttributeSetBase();
//		AttributeSetBase = new UCoreAttributeSet

		InitializeAttributes();
	}

	// ASC MixedMode replication requires that the ASC Owner's Owner be the Controller.
	SetOwner(NewController);
}

void ASSSCharacterBase::InitializeAttributes() {
	if (!AbilitySystemComponent.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Ability system component is invalid for %s. Unable to intialize attributes"), *FString(__FUNCTION__), *GetName());
		return;
	}

	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, GetCharacterLevel(), EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	}
}

int32 ASSSCharacterBase::GetCharacterLevel() const
{
	if (AttributeSetBase)
	{
		return 1;//return static_cast<int32>(AttributeSetBase->GetCharacterLevel());
	}

	return 0;
}
