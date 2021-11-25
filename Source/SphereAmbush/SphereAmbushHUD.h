// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Public/GameStatsWidget.h"

#include "SphereAmbushHUD.generated.h"

UCLASS()
class ASphereAmbushHUD : public AHUD
{
	GENERATED_BODY()

public:
	ASphereAmbushHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	UFUNCTION()
	void UpdateInnerSphereCount(int value);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> GameStatsClass{nullptr};

private:
	UGameStatsWidget* StatsWidget{ nullptr };
};

