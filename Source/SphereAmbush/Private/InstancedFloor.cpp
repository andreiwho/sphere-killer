// Fill out your copyright notice in the Description page of Project Settings.


#include "InstancedFloor.h"

// Sets default values
AInstancedFloor::AInstancedFloor()
    : InstancedMesh(CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedMesh")))
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

void AInstancedFloor::GenerateMesh()
{
    // Clear the mesh
    InstancedMesh->ClearInstances();

    // Allocate an array to hold the GridSize^2 transform instances
    TArray<FTransform> instanceTransforms;
    instanceTransforms.Reserve(GridSize * GridSize);

    // Store it here to not recreate the transform each time in a loop
    FTransform transform{ FTransform::Identity };


    // Generate transforms for instances
    auto meshBounds = InstancedMesh->GetStaticMesh()->GetBounds().GetBox().GetSize();
    for (int x = -GridSize / 2; x < GridSize / 2; ++x)
    {
        for (int y = -GridSize / 2; y < GridSize / 2; ++y)
        {
            // Calculate the position of the new instance
            FVector position = {
                static_cast<float>(x) * meshBounds.X + (GridSpacing * x),
                static_cast<float>(y) * meshBounds.X + (GridSpacing * y),
                0.0f
            };

            transform.SetTranslation(position);
            instanceTransforms.Add(transform);
            // InstancedMesh->AddInstance(transform);
        }
    }

    // Put instances into the mesh
    InstancedMesh->AddInstances(instanceTransforms, false);

    InstancedMesh->MarkRenderStateDirty();
}

// Called every frame
void AInstancedFloor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

