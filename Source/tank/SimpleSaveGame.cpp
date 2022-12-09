// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleSaveGame.h"
#include "SimpleSavingActorSubsystem.h"
#include "BasicClass.h"
#include "HealthComponent.h"
#include "InventoryCharacter.h"
#include "InventoryComponent.h"

void USimpleSaveGame::CollectData(UWorld* World)
{
	auto MySubsystem = World->GetSubsystem<USimpleSavingActorSubsystem>();
	for (auto Actor : MySubsystem->GetEnemies())
	{
		ABasicClass* Enemy = Cast<ABasicClass>(Actor.Value);
		EnemyInfo.Add(
			Actor.Key,
			FEnemyInfo(
				Enemy->GetHealthComponent()->GetHealth(),
				Enemy->GetCurrentAmmo(),
				Enemy->GetActorLocation(),
				Enemy->GetGunTransform(),
				Enemy->GetBaseTransform()
		));
	}

	if (ABasicClass* PlayerPawn = Cast<ABasicClass>(World->GetFirstPlayerController()->GetPawn()))
	{
		TMap<int, FInventorySlotInfo> Items = PlayerPawn->GetInventoryComponent()->GetItems();
		CharInfo.Add(
			PlayerPawn->GetName(),
			FCharacterInfo(
				PlayerPawn->GetHealthComponent()->GetHealth(),
				PlayerPawn->GetCurrentAmmo(),
				Items,
				PlayerPawn->GetActorLocation(),
				PlayerPawn->GetGunTransform(),
				PlayerPawn->GetBaseTransform()
		));
	}
}

void USimpleSaveGame::ApplyData(UWorld* World)
{
	auto MySubsystem = World->GetSubsystem<USimpleSavingActorSubsystem>();
	for (auto Actor : EnemyInfo)
	{
		if (ABasicClass* Enemy = Cast<ABasicClass>(*MySubsystem->GetEnemies().Find(Actor.Key)))
		{
			Enemy->GetHealthComponent()->SetHealth(Actor.Value.Health);
			Enemy->SetCurrentAmmo(Actor.Value.Ammo);
			Enemy->SetActorLocation(Actor.Value.EnemyLocation);
			Enemy->SetGunTransform(Actor.Value.GunTransform);
			Enemy->SetBaseTransform(Actor.Value.BaseTransform);
		}
	}

	for (auto Actor : CharInfo)
	{
		if (ABasicClass* PlayerPawn = Cast<ABasicClass>(World->GetFirstPlayerController()->GetPawn()))
		{
			PlayerPawn->GetHealthComponent()->SetHealth(Actor.Value.Health);
			PlayerPawn->SetCurrentAmmo(Actor.Value.Ammo);
			PlayerPawn->GetInventoryComponent()->SetItems(Actor.Value.Items);
			PlayerPawn->SetActorLocation(Actor.Value.TankLocation);
			PlayerPawn->SetGunTransform(Actor.Value.GunTransform);
			PlayerPawn->SetBaseTransform(Actor.Value.BaseTransform);
		}
	}
}
