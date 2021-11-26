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

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void SetSphereCount(int count);
	void SetScore(int score);
	void SetWave(int wave);
private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> GameStatsClass;

	class UGameStatsWidget* GameStats{nullptr};
};

