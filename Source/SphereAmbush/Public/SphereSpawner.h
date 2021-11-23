// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SphereSpawner.generated.h"

UCLASS()
class SPHEREAMBUSH_API ASphereSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASphereSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void SpawnSpheres();
private:
	static constexpr float s_SphereZ = 300.0f;

	UPROPERTY(EditAnywhere)
	class UClass* SphereSpawnClass{nullptr};

	UPROPERTY(EditAnywhere)
	int SphereCount{ 15 };

	UPROPERTY(EditAnywhere)
	float SpawnRadius{ 2000.0f };

	UPROPERTY(EditAnywhere)
	float MinSphereDistance{ 80.0f };

	UPROPERTY(EditAnywhere)
	float WaveRadiusChangeRate{ 0.05f };

	UPROPERTY(EditAnywhere)
	float WaveSpeedChangeRate{ 0.03f };
};
