// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameStructs.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDie);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, DamageValue);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANK_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Health Values")
	float MaxHealth = 10;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnDie OnDie; 

	UFUNCTION(BlueprintCallable, Category = "Health Component")
  	void DamageTake(const FDamageData& DamageData);

	UFUNCTION(BlueprintCallable, Category = "Health Component")
	float GetHealth() const;

	void SetHealth(float InHealth) {
		CurrentHealth = InHealth;
	}

	UFUNCTION(BlueprintCallable, Category = "Health Component")
	float GetHealthState() const;

	UFUNCTION(BlueprintCallable, Category = "Health Component")
	void AddHealth(float AdditionalHealthValue);

protected:
	UPROPERTY()
	float CurrentHealth = 0;
	 
	virtual void BeginPlay() override;
		
};
