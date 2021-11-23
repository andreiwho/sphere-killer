// Fill out your copyright notice in the Description page of Project Settings.


#include "InstancedFloor.h"

// Sets default values
AInstancedFloor::AInstancedFloor()
	:	InstancedMesh(CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedMesh")))
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(InstancedMesh);
}

// Called when the game starts or when spawned
void AInstancedFloor::BeginPlay()
{
	Super::BeginPlay();
}

void AInstancedFloor::GenerateMesh() {
	InstancedMesh->ClearInstances();

	// Store it here to not recreate the transform each time in a loop
	FTransform transform{FTransform::Identity};

	auto meshBounds = InstancedMesh->GetStaticMesh()->GetBounds().GetBox().GetSize();

	for (unsigned int x = 0; x < GridSize; ++x) {
		for (unsigned int y = 0; y < GridSize; ++y) {
			// Calculate the position of the new instance
			FVector position = {
				static_cast<float>(x) * meshBounds.X + (GridSpacing*x),
				static_cast<float>(y) * meshBounds.X + (GridSpacing*y),
				0.0f
			};

			transform.SetTranslation(position);
			InstancedMesh->AddInstance(transform);

			// Just for logging (not really neaded in Dist)
#ifndef DEBUG
			UE_LOG(LogTemp, Warning, TEXT("Created floor instance with bounds: %s"), *meshBounds.ToString());
#endif
		}
	}

}

// Called every frame
void AInstancedFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

