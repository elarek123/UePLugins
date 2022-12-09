// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Input/DragAndDrop.h>
#include "DraggableItem.generated.h"

/**
 * 
 */
UCLASS()
class TANK_API UDraggableItem : public UUserWidget
{
	GENERATED_BODY()
	

public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TankText;

	UPROPERTY(EditAnywhere)
	FText TankName;

	virtual void NativePreConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	UFUNCTION()
	void ReleaseVisual(UDragDropOperation* InOperation);

	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
