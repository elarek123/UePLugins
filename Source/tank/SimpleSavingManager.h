// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SimpleSavingManager.generated.h"

class USaveGame;
class USimpleSaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveAction, const FString&, SlotName);

UCLASS()
class TANK_API USimpleSavingManager : public UObject
{
	GENERATED_BODY()

public:
	void Init();

	virtual UWorld* GetWorld() const override
	{
		return HasAnyFlags(RF_ClassDefaultObject) ? nullptr : GetOuter()->GetWorld();
	}

	UPROPERTY(BlueprintAssignable)
	FOnSaveAction OnGameSaved;

	UPROPERTY(BlueprintAssignable)
	FOnSaveAction OnGameLoaded;

	UFUNCTION(BlueprintPure)
	bool IsSaveGameExist(const FString& SlotName) const;

	UFUNCTION(BlueprintCallable)
	void LoadGame(const FString& SlotName);

	UFUNCTION(BlueprintCallable)
	void SaveGame(const FString& SlotName);

	USimpleSaveGame* GetCurrentSave() const { return  CurrentSave; }

protected:

	void OnGameLoadFunc(const FString& SlotName, const int32 UserIndex, USaveGame* SaveGame);

	void OnGameSaveFunc(const FString& SlotName, const int32 UserIndex, bool bSuccess);

	UPROPERTY(BlueprintReadWrite)
	USimpleSaveGame* CurrentSave;
};
