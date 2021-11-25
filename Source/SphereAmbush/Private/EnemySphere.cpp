// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySphere.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "SphereSpawner.h"
#include "EngineUtils.h"

#include "../SphereAmbushProjectile.h"

// Sets default values
AEnemySphere::AEnemySphere()
    : StaticMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"))),
        AirWavingComponent(CreateDefaultSubobject<UAirWaving>(TEXT("Waving"))),
        EmitterComponent(CreateDefaultSubobject<UEmitterOnDestroy>(TEXT("Destroy Emitter"))) {

    PrimaryActorTick.bCanEverTick = false;
    SetRootComponent(StaticMesh);
}

// Called when the game starts or when spawned
void AEnemySphere::BeginPlay() {
    Super::BeginPlay();
    Player = GetWorld()->GetFirstPlayerController();
    check(Player != nullptr);

    Physics = Cast<UPrimitiveComponent>(GetComponentByClass(UPrimitiveComponent::StaticClass()));
    check(Physics != nullptr);

    Physics->OnComponentHit.AddDynamic(this, &AEnemySphere::OnHit);

    // Get distance to player for this sphere
    DistanceToPlayer = FVector::Distance(GetActorLocation(), GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
}


void AEnemySphere::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
    if ((OtherActor != nullptr) && (OtherActor != this)) {
        // TODO: Check if this needs to be changed
        if (Cast<ASphereAmbushProjectile>(OtherActor)) {
            Destroy();
        }
    }
}

void AEnemySphere::Destroyed() {
    NotifySpawner();
    Super::Destroyed();
}

void AEnemySphere::NotifySpawner() {
    // The scene should have only one sphere spawner
    for (TActorIterator<ASphereSpawner> it(GetWorld()); it; ++it) {
        it->OnSphereDestroyed(DistanceToPlayer);
    }
}

// Called every frame
void AEnemySphere::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

