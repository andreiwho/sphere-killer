// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereSpawner.h"
#include "Math/UnrealMathUtility.h"
#include "EnemySphere.h"
#include "DrawDebugHelpers.h"

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

	// Debug draw spawn zones
	{
		FTransform sceneCenter{ FTransform::Identity };
		sceneCenter.SetRotation(FQuat{ FVector{ 0.0f, 1.0f, 0.0f }, FMath::DegreesToRadians(90.0f) });
		sceneCenter.SetTranslation({ 0.0f, 0.0f, 55.0f });
		// Draw the debug circle for inner spawn zone
		static constexpr int32 CIRCLE_SEGMENTS = 64;
		DrawDebugCircle(GetWorld(), sceneCenter.ToMatrixNoScale(), InnerSpawnRadius, CIRCLE_SEGMENTS, FColor::Red, false, -1.0f, 0U, 4.0f, false);

		// Draw debug circle for the outer spawn zone
		DrawDebugCircle(GetWorld(), sceneCenter.ToMatrixNoScale(), OuterSpawnRadius, CIRCLE_SEGMENTS, FColor::Blue, false, -1.0f, 0U, 4.0f, false);
	}
}

// Get a random point within the radius
static FVector PickRandomPointInRadius(const FVector& origin, const float minDistanceFromOrigin, const float radius, bool bUseRandomSphereHeight = true, float minZ = 200.0f, float maxZ = 500.0f) {
	// Get radius for random inner circle
	float distance = FMath::RandRange(minDistanceFromOrigin, radius);
	
	// Get the angle of the circle to pick a point at the edge 
	float angle = FMath::RandRange(0.0f, 359.99f);

	float zPosition = 200.0f;
	if (bUseRandomSphereHeight) {
		zPosition = FMath::RandRange(minZ, maxZ);
	}

	FVector newPosition = {
		FMath::Sin(angle) * distance,
		FMath::Cos(angle) * distance,
		zPosition
	};

	return origin + newPosition;
}

void ASphereSpawner::SpawnSpheres() 
{
	static constexpr float MinDistanceFromCenter = 160.0f;

	// Get the player positition and set own location to this value
	// Every wave starts from the players' position
	FVector playerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	SetActorLocation(playerPosition);

	// Keep track of all positions to prevent sphere overlapping
	TArray<FVector> positions{};
	positions.Reserve(OverallSphereCount);

	// Lambda for sphere spawning
	auto spawnSpheres = [&](int count, float innerRadius, float outterRadius) {
		for (int i = 0; i < count; ++i) {
			FVector point = PickRandomPointInRadius(GetActorLocation(), innerRadius, outterRadius, bUseRandomSphereHeight, MinZValue, MaxZValue);
			FTransform transform{ FTransform::Identity };
			transform.SetLocation(point);
			transform.SetScale3D(FVector{ SphereRadiusScale });

			GetWorld()->SpawnActor(SphereSpawnClass, &transform);
		}
	};

	check(InnerSphereCount <= OverallSphereCount);
	// Spawn main spheres inside the nearest inner circle (the circle needed to finish the wave)
	spawnSpheres(InnerSphereCount, MinDistanceFromCenter, InnerSpawnRadius);

	// Spawn bonus spheres outside the inner circle
	spawnSpheres(OverallSphereCount - InnerSphereCount, InnerSpawnRadius, OuterSpawnRadius);
}

