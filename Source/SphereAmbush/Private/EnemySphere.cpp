// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySphere.h"
#include "Components/SphereComponent.h"
#include "../SphereAmbushProjectile.h"

// Sets default values
AEnemySphere::AEnemySphere()
    : StaticMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"))),
    CollisionComp(CreateDefaultSubobject<USphereComponent>(TEXT("Collision"))) {
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    SetRootComponent(StaticMesh);
    StaticMesh->SetSimulatePhysics(true);

    CollisionComp->InitSphereRadius(100.0f);
    CollisionComp->OnComponentHit.AddDynamic(this, &AEnemySphere::OnHit);
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
    auto playerPawn = Player->GetPawn();

    FVector playerForward = playerPawn->GetActorForwardVector();
    FVector playerLocation = playerPawn->GetActorLocation();
    FVector thisLocation = GetActorLocation();
    FVector newLocation = FMath::VInterpTo(thisLocation, playerLocation + playerForward, DeltaTime, ChasingSpeed);

    SetActorLocation(newLocation);
}

