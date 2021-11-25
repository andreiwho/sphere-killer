// Fill out your copyright notice in the Description page of Project Settings.


#include "EmitterOnDestroy.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UEmitterOnDestroy::UEmitterOnDestroy()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEmitterOnDestroy::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UEmitterOnDestroy::OnComponentDestroyed(bool bDerrived) {
	check(ParticleSystem);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetOwner()->GetTransform());
	Super::OnComponentDestroyed(bDerrived);
}


// Called every frame
void UEmitterOnDestroy::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

