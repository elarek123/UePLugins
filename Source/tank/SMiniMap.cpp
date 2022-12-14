// Fill out your copyright notice in the Description page of Project Settings.

#include "SMiniMap.h"
#include "Rendering/DrawElements.h"
#include "Styling/CoreStyle.h"
#include "SlateOptMacros.h"
#include "MyCoreStyle.h"
#include <Kismet/KismetMathLibrary.h>

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMiniMap::Construct(const FArguments& InArgs)
{
	Obstacles = InArgs._Obstacles;
	PlayerPos = InArgs._PlayerPos;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

int32 SMiniMap::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	const FVector2D LocalSize = AllottedGeometry.GetLocalSize();

	TArray<FVector2D> Border;
	Border.Add(LocalSize * FVector2D(0.f, 0.f));
	Border.Add(LocalSize * FVector2D(0.f, 1.f));
	Border.Add(LocalSize * FVector2D(1.f, 1.f));
	Border.Add(LocalSize * FVector2D(1.f, 0.f));
	Border.Add(LocalSize * FVector2D(0.f, 0.f));

	FSlateDrawElement::MakeLines(
		OutDrawElements,
		LayerId,
		AllottedGeometry.ToPaintGeometry(),
		Border
	);

	for (auto& Obs : Obstacles)
	{
		TArray<FVector2D> Points;
		Points.Add(LocalSize * Obs.Min);
		Points.Add(LocalSize * Obs.Max);

		FSlateDrawElement::MakeLines(
			OutDrawElements,
			LayerId,
			AllottedGeometry.ToPaintGeometry(),
			Points
		);
	}

	FSlateBrush Brush = *MyCoreStyle::Get().GetBrush("PlayerImage");
	FSlateBrush Brush2 = *MyCoreStyle::Get().GetBrush("BordersImage");

	float BorderSize = UKismetMathLibrary::Abs(Border[0].X - Border[1].X) ? UKismetMathLibrary::Abs(Border[0].X - Border[1].X) : UKismetMathLibrary::Abs(Border[0].Y - Border[1].Y);
	Brush2.SetImageSize(FVector2D(BorderSize, BorderSize));

	FSlateDrawElement::MakeBox(
		OutDrawElements,
		LayerId,
		AllottedGeometry.ToPaintGeometry(Brush2.ImageSize * 0.f, Brush2.ImageSize),
		&Brush2
	);

	const FVector2D PlayerPos2D = PlayerPos.Get();

	FSlateDrawElement::MakeBox(
		OutDrawElements,
		LayerId,
		AllottedGeometry.ToPaintGeometry(LocalSize * PlayerPos2D - Brush.ImageSize * 0.5f, Brush.ImageSize),
		&Brush
	);

	return 0;
}

FVector2D SMiniMap::ComputeDesiredSize(float LayoutScaleMultiplier) const
{
	return FVector2D(200.f);
}