// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySphere.h"
#include "Components/SphereComponent.h"
#include "../SphereAmbushProjectile.h"

// Sets default values
AEnemySphere::AEnemySphere()
    : StaticMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"))),
        AirWavingComponent(CreateDefaultSubobject<UAirWaving>(TEXT("Waving"))) {

    PrimaryActorTick.bCanEverTick = true;
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
}


void AEnemySphere::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
    if ((OtherActor != nullptr) && (OtherActor != this)) {
        // TODO: Check if this needs to be changed
        if (Cast<ASphereAmbushProjectile>(OtherActor)) {
            UE_LOG(LogTemp, Warning, TEXT("Hit"));
            Destroy();
        }
    }
}

// Called every frame
void AEnemySphere::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

