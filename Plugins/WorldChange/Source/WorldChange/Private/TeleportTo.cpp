// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportTo.h"
#include <Components/SceneComponent.h>
#include <Components/PointLightComponent.h>
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
ATeleportTo::ATeleportTo()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceneComp;

	GatesMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gates Mesh"));
	GatesMesh->SetupAttachment(sceneComp);

	ActivatedLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Activated lights"));
	ActivatedLight->SetupAttachment(sceneComp);

	DeactivatedLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Deactivated lights"));
	DeactivatedLight->SetupAttachment(sceneComp);

	TriggerCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger collider"));
	TriggerCollider->SetupAttachment(sceneComp);

	TriggerCollider->OnComponentBeginOverlap.AddDynamic(this, &ATeleportTo::OnTriggerOverlapBegin);




}

void ATeleportTo::BeginPlay()
{
	Super::BeginPlay();
	SetActiveLights();
}

void ATeleportTo::SetIsActivated(bool NewIsActivated)
{
	bIsActivated = NewIsActivated;
	SetActiveLights();
}

void ATeleportTo::SetActiveLights()
{
	ActivatedLight->SetHiddenInGame(!bIsActivated);
	DeactivatedLight->SetHiddenInGame(bIsActivated);
}

void ATeleportTo::OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsActivated)
		return;
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (OtherActor == PlayerPawn) {
		UGameplayStatics::OpenLevel(GetWorld(), LoadLevelName);
	}
}

