// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereSpawner.h"
#include "Math/UnrealMathUtility.h"
#include "EnemySphere.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"

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

	// Bind regen to space for debug purposes
	PlayerInputComponent = Cast<UInputComponent>(GetWorld()->GetFirstPlayerController()->GetComponentByClass(UInputComponent::StaticClass()));
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ASphereSpawner::NextWave);
	
	// Set the origin
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
		sceneCenter.SetTranslation({SpawnOrigin.X, SpawnOrigin.Y, 55.0f });
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

// Just boilerplate. 
static AActor* SpawnSingleSphere(UWorld* world, UClass* klass, const FVector& location, const float scale) {
	FTransform transform{ FTransform::Identity };
	transform.SetLocation(location);
	transform.SetScale3D(FVector{ scale });
	return world->SpawnActor(klass, &transform);
}

void ASphereSpawner::SpawnSpheres() 
{
	static constexpr float MinDistanceFromCenter = 250.0f;

	// Clear spheres before creating new ones
	ClearSpheres();

	// Get the player positition and set own location to this value
	// Every wave starts from the players' position
	SpawnOrigin = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	// Keep track of all positions to prevent sphere overlapping
	TArray<FVector> positions{};
	positions.Reserve(OverallSphereCount);

	// Lambda for sphere spawning
	auto Spawn = [&](int count, float innerRadius, float outterRadius) {
		int spawnedSpheresCount = 0;
		while(spawnedSpheresCount < count) {
			FVector point = PickRandomPointInRadius(SpawnOrigin, innerRadius, outterRadius, bUseRandomSphereHeight, MinZValue, MaxZValue);

			// Check if distance is less than minDist, if yes -> return
			if (positions.Num() == 0) {
				SpawnSingleSphere(GetWorld(), SphereSpawnClass, point, SphereRadiusScale);
				positions.Add(point);
			} else {
				// Sort the positions of the spheres to get the lowest one at the beginning
				// Maybe not really fast, but for not really big amount of spheres, it may not take a lot time
				positions.Sort([&](const FVector& lhs, const FVector& rhs) {
					const float lhsDist = FVector::Distance(point, lhs);
					const float rhsDist = FVector::Distance(point, rhs);
					return lhsDist < rhsDist;
				});

				
				// Have to calculate the bias since spheres change sizes per wave
				constexpr float approxSphereBaseRadius = 50.0f;
				const float distanceBias = (approxSphereBaseRadius * 2 * SphereRadiusScale);
				
				// If the distance is less than allowed for the spheres, then create one, otherwise continue
				float distanceToClosestSphere = FVector::Distance(point, positions[0]);
				if (distanceToClosestSphere >= MinSphereDistance + distanceBias) {
					// UE_LOG(LogTemp, Warning, TEXT("Spawning a sphere at %f from the closest sphere"), distanceToClosestSphere);
					SpawnSingleSphere(GetWorld(), SphereSpawnClass, point, SphereRadiusScale);
					positions.Add(point);
				} else {
					continue;
				}
			}

			++spawnedSpheresCount;
		}
	};

	check(InnerSphereCount <= OverallSphereCount);

	// Spawn main spheres inside the nearest inner circle (the circle needed to finish the wave)
	Spawn(InnerSphereCount, MinDistanceFromCenter, InnerSpawnRadius);

	// Spawn bonus spheres outside the inner circle
	Spawn(OverallSphereCount - InnerSphereCount, InnerSpawnRadius, OuterSpawnRadius);
}

void ASphereSpawner::ClearSpheres() {
	TArray<AEnemySphere*> spheres{};
	for (TActorIterator<AEnemySphere> it{ GetWorld() }; it; ++it) {
		it->Destroy();
	}
}

void ASphereSpawner::NextWave() {
	ClearSpheres();
	
	// Set location to the players position
	SpawnOrigin = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	WaveIndex++;
	
	// Change sphere count for the next wave
	OverallSphereCount += static_cast<int>(static_cast<float>(OverallSphereCount) * WaveSphereCountChangeRate);

	// Change sphere radius for the next wave
	SphereRadiusScale -= SphereRadiusWaveFactor;
	SphereRadiusScale = FMath::Clamp(SphereRadiusScale, 0.05f, 100.0f);

	// Increase the outer spawn radius
	OuterSpawnRadius += static_cast<int>(static_cast<float>(OuterSpawnRadius) * WaveRadiusChangeRate);


	SpawnSpheres();
}

