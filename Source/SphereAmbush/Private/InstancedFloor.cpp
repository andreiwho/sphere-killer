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
    Transforms.Reset();
    // Allocate an array to hold the GridSize^2 transform instances
    
    struct Range
    {
        int minX, X;
        int minY, Y;
    };

    // Ranges for random splitting floor generation
    TArray<Range> ranges{};
    ranges.Add({ -GridSize / 2,  0,                 -GridSize / 2,   0});
    ranges.Add({ 0,              GridSize / 2,      0,               GridSize / 2});
    ranges.Add({ -GridSize / 2,  0,                 0,               GridSize / 2});
    ranges.Add({ 0,              GridSize / 2,      -GridSize / 2,   0 });


    // Generate transforms for every of the ranges
    for (Range range : ranges)
    {
        Transforms.Add(Async(EAsyncExecution::ThreadPool, [this, range]()
        {
            TArray<FTransform> instanceTransforms;
            instanceTransforms.Reserve(GridSize * GridSize);

            // Store it here to not recreate the transform each time in a loop
            FTransform transform{ FTransform::Identity };

            // Generate transforms for instances
            auto meshBounds = InstancedMesh->GetStaticMesh()->GetBounds().GetBox().GetSize();

            for (int x = range.minX; x < range.X; ++x)
            {
                for (int y = range.minY; y < range.Y; ++y)
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

            return instanceTransforms;
        }));
    }

    for (auto& transform : Transforms)
    {
        transform.Wait();
        if (transform.IsReady())
        {
            InstancedMesh->AddInstances(transform.Get(), false);
            bDelayed = false;
        }
    }

    Transforms.Empty();
    InstancedMesh->MarkRenderStateDirty();
}

// Called every frame
void AInstancedFloor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

