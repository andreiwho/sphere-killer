// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereSpawner.h"
#include "Math/UnrealMathUtility.h"
#include "EnemySphere.h"

// Sets default values
ASphereSpawner::ASphereSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASphereSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnSpheres();
}

// Called every frame
void ASphereSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASphereSpawner::SpawnSpheres() 
{
	FVector playerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	// TODO: Spawn spheres not ON THE CIRCLE but within the CIRCLE... A little misunderstanding going on there
	for (int i = 0; i < SphereCount; ++i) {
		float random = FMath::RandRange(0.0f, 359.99f);
		
		FVector position{
			FMath::Sin(random) * SpawnRadius,
			FMath::Cos(random) * SpawnRadius,
			s_SphereZ
		};

		FActorSpawnParameters params{};
		FTransform transform{};
		transform.SetTranslation(playerPosition + position);

		AActor* sphere = GetWorld()->SpawnActor<AActor>(SphereSpawnClass, transform);
		sphere->SetActorLocation(position);
	}
}

