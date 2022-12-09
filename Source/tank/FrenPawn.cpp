// Fill out your copyright notice in the Description page of Project Settings.


#include "FrenPawn.h"
#include "BasicClass.h"

TArray<ABasicClass*> FrenPawn::BasicClasss;

void FrenPawn::AddPawn(ABasicClass* AddablePawn)
{
	BasicClasss.Add(AddablePawn);
}

void FrenPawn::DelPawn(ABasicClass* DeletablePawn)
{
	BasicClasss.Remove(DeletablePawn);
}

TMap<double, ABasicClass*> FrenPawn::GetUnFriendly(ABasicClass* ThisPawn)
{
	TMap<double, ABasicClass*> Targets;

	for (auto& i : BasicClasss)
	{
		if (i && ThisPawn && (*i).GetFriendness() != (*ThisPawn).GetFriendness())
		{
			FVector a = ThisPawn->GetActorLocation();
			FVector b = i->GetActorLocation();
			Targets.Add(FVector::Dist(ThisPawn->GetActorLocation(), i->GetActorLocation()), i);
		}
	}

	Targets.KeySort([](double a, double b) {return a < b; });

	return Targets;
}
