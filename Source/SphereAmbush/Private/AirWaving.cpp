// Fill out your copyright notice in the Description page of Project Settings.


#include "AirWaving.h"

// Sets default values for this component's properties
UAirWaving::UAirWaving()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	AnimationTimeOffset = FMath::RandRange(0.0f, 60.0f);
}


// Called when the game starts
void UAirWaving::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAirWaving::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Use waving animation
	float currentTime = GetWorld()->GetTimeSeconds() + AnimationTimeOffset;
	float zPos = FMath::Sin(currentTime);

	auto location = GetOwner()->GetActorLocation();
	location.Z += zPos * DeltaTime * 10.0f;
	GetOwner()->SetActorLocation(location);
}

