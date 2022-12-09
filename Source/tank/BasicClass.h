// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>
#include "Cannon.h"
#include "Damageable.h"
#include "GameStructs.h"
#include <Components/BoxComponent.h>
#include "HealthComponent.h"
#include "AmmoBox.h"
#include <Components/Widget.h>
#include <Components/WidgetComponent.h>
#include "HealthBar.h"
#include "InventoryCharacter.h"
#include <Engine/EngineTypes.h>
#include "BasicClass.generated.h"

UCLASS()
class TANK_API ABasicClass : public AInventoryCharacter, public IDamageable
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasicClass();

	virtual void Serialize(FArchive& Ar) override;

	virtual void DamageTake(const FDamageData& DamageData) override;

	FTransform GetBaseTransform(){
		return BodyMesh->GetRelativeTransform();
	}

	void SetBaseTransform(FTransform InTransform) {
		BodyMesh->SetRelativeTransform(InTransform);
	}
	FTransform GetGunTransform() {
		return TurretMesh->GetRelativeTransform();
	}
	void SetGunTransform(FTransform InTransform) {
		TurretMesh->SetRelativeTransform(InTransform);
	}

	UInventoryComponent* GetInventoryComponent() {
		return LocalInventory;
	}

	bool bIsDead = false;

	UFUNCTION(BlueprintCallable, Category = "Friendness")
	bool GetFriendness() {
		return bIsFriendly;
	}

	UFUNCTION(BlueprintCallable, Category = "Friendness")
	void SetFriendness(bool InFriendness) {
		bIsFriendly = InFriendness;
	}

	FVector GetTurretLocation() {
		return TurretMesh->GetComponentLocation();
	}
	UHealthComponent* GetHealthComponent() {
		return HealthComponent;
	}
	class UHealthBar* Health;
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	UInventoryManagerComponent* GetInventoryManager() {
		return InventoryManager;
	}
	int GetCurrentAmmo() {
		return CannonPack[0]->GetAmmoParam(1);
	}
	void SetCurrentAmmo(int InCount) {
		return CannonPack[0]->SetAmmo(InCount);
	}
protected:
	UPROPERTY(VisibleDefaultsOnly, BluePrintReadWrite, Category = "Components")
		class UWidgetComponent* HealthBar;

	UPROPERTY(VisibleDefaultsOnly, BluePrintReadWrite, Category = "Components")
		class UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BluePrintReadWrite, Category = "Components")
		class UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UArrowComponent* CannonSpawnPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UArrowComponent* AmmoBoxSpawnPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UBoxComponent* HitCollider;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UHealthComponent* HealthComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UParticleSystemComponent* DestroyEffect;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UAudioComponent* AudioDestroyEffect;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Turret")
		float TurretRotationSmoothness = 0.1;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Turret")
		TSubclassOf<class ACannon> DefaultCannonClass;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Turret")
		TArray <class ACannon*>  CannonPack;

	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Turret")
		float DestroyRate = 0.75;

	class AMenuHud* TanksHud;

	UFUNCTION(BlueprintNativeEvent, Category = "Health")
		void OnHealthChanged(float Damage);

	UFUNCTION(BlueprintNativeEvent, Category = "Health")
		void OnDie();

	UPROPERTY(EditDefaultsOnly, Category = "Friendliness")
		bool bIsFriendly = false;

	void Destroying();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo Box")
		TSubclassOf<class AAmmoBox> Ammo_Box;

	bool bIsPlayer;

	FTimerHandle ReloadTimerHandle;
};
