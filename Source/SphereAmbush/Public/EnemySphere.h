// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySphere.generated.h"

UCLASS()
class SPHEREAMBUSH_API AEnemySphere : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySphere();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMesh{ nullptr };

	UPROPERTY(VisibleAnywhere)
	class APlayerController* Player{ nullptr };

	UPROPERTY(EditAnywhere)
	float ChasingSpeed = 10.0f;

	class UPrimitiveComponent* Physics{nullptr};

	class USphereComponent* CollisionComp{ nullptr };
};
