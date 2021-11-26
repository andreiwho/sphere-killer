// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <cstdint>
#include "GameFramework/Actor.h"
#include "InstancedFloor.generated.h"


UCLASS()
class SPHEREAMBUSH_API AInstancedFloor : public AActor {
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AInstancedFloor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable)
    void GenerateMesh();

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    // The size of the instanced grid
    UPROPERTY(EditAnywhere)
    int GridSize{ 10 };

    // The spacing between each grid cell
    UPROPERTY(EditAnywhere)
    float GridSpacing{ 5.0f };

private:
    // Static mesh component that will be used for the floor of the level
    UPROPERTY(VisibleAnywhere)
    class UInstancedStaticMeshComponent* InstancedMesh{ nullptr };

    TArray<TFuture<TArray<FTransform>>> Transforms{};

    bool bDelayed = true;
};
