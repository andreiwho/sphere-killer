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
	void ClearSpheres();
	void NextWave();
	void OnSphereDestroyed(float distance);
private:
	static constexpr float s_SphereZ = 300.0f;
	
private:	
	FVector SpawnOrigin{};

	int WaveIndex = 0;

	UPROPERTY(EditAnywhere)
	bool bUseRandomSphereHeight{ true };

	UPROPERTY(EditAnywhere)
	float MinZValue{ 200.0f };

	UPROPERTY(EditAnywhere)
	float MaxZValue{ 500.0f };


	UPROPERTY(EditAnywhere)
	class UClass* SphereSpawnClass{nullptr};

	class UInputComponent* PlayerInputComponent{ nullptr };

	UPROPERTY(EditAnywhere)
	int InnerSphereCount{ 10 };

	UPROPERTY(EditAnywhere)
	int OverallSphereCount{ 15 };

	UPROPERTY(EditAnywhere)
	float InnerSpawnRadius{ 1500.0f };

	UPROPERTY(EditAnywhere)
	float OuterSpawnRadius{ 2000.0f };

	UPROPERTY(EditAnywhere)
	float MinSphereDistance{ 80.0f };

	UPROPERTY(EditAnywhere)
	float WaveRadiusChangeRate{ 0.05f };

	UPROPERTY(EditAnywhere)
	float WaveSphereCountChangeRate{ 0.1f };

	UPROPERTY(EditAnywhere)
	float SphereRadiusScale{ 0.5f };

	// Each wave the spawned sphere will be smaller by this factor value
	UPROPERTY(EditAnywhere)
	float SphereRadiusWaveFactor{ 0.005f };

private:
	int CurrentInnerSpheres{ 0 };
	int CurrentOuterSpheres{ 0 };
};
