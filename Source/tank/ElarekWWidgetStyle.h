// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"

#include "ElarekWWidgetStyle.generated.h"

/**
 *
 */
USTRUCT()
struct TANK_API FElarekWStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

		FElarekWStyle();
	virtual ~FElarekWStyle();

	UPROPERTY(EditAnywhere, Category = Appearance)
		FCheckBoxStyle CheckBoxStyle;

	UPROPERTY(EditAnywhere, Category = Appearance)
		FTextBlockStyle TextBlockStyle;

	// FSlateWidgetStyle 
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FElarekWStyle& GetDefault();
};

/**
 */
UCLASS(hidecategories = Object, MinimalAPI)
class UElarekWWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category = Appearance, EditAnywhere, meta = (ShowOnlyInnerProperties))
		FElarekWStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast<const struct FSlateWidgetStyle*>(&WidgetStyle);
	}
};