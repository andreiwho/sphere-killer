// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EmitterOnDestroy.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPHEREAMBUSH_API UEmitterOnDestroy : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEmitterOnDestroy();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void OnComponentDestroyed(bool) override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* ParticleSystem{ nullptr };
};
