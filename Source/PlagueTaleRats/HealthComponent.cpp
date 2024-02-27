// Copyright Srujan Lokhande 2024

#include "HealthComponent.h"
#include "Utils.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UHealthComponent::UpdateHealth(float InHealth)
{
	CurrentHealth -= InHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);

	if(FMath::IsNearlyZero(CurrentHealth))
	{		
		GetOwner()->Destroy();
	}
}



