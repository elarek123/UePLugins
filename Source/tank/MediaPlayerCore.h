// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MediaPlayerCore.generated.h"

/**
 *
 */
UCLASS()
class TANK_API UMediaPlayerCore : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnPlayClicked();

	UFUNCTION()
		void OnStopClicked();

	UFUNCTION()
		void OnBrowseClicked();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UImage* OutputImage;

	UPROPERTY(EditDefaultsOnly)
		class UMaterialInterface* Material;

	UPROPERTY(EditAnywhere)
		class UMediaPlayer* MediaPlayer;

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		class UButton* Play;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		class UButton* Stop;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		class UButton* Browse;

	UFUNCTION(BlueprintCallable)
	int IsVideo();

	bool bIsVideo = false;

	UPROPERTY()
		class UMaterialInstanceDynamic* MaterialInstanceDynamic = nullptr;
};
