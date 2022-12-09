// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsProjectile.h"
#include "Projectile.h"
#include "Damageable.h"
#include "GameStructs.h"



APhysicsProjectile::APhysicsProjectile()
{
	MoveComponent = CreateDefaultSubobject<UPhysicsMovementComponent>(TEXT("Movement Component"));
}

void APhysicsProjectile::Start()
{
	Super::Start();

	MoveComponent->Velocity = GetActorForwardVector() * MoveSpeed;
	MoveComponent->SetComponentTickEnabled(true);
}

void APhysicsProjectile::Stop()
{
	MoveComponent->Velocity = FVector::ZeroVector;
	MoveComponent->SetComponentTickEnabled(false);
	Super::Stop();
}

void APhysicsProjectile::Tick(float DeltaTime)
{
	if (GetActorLocation().Z < -1000)
		Stop();
}
