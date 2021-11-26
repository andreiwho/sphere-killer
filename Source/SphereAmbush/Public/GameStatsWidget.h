// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStatsWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPHEREAMBUSH_API UGameStatsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UGameStatsWidget(const FObjectInitializer& initializer);

	void SetSphereCount(int count);
	void SetScore(int score);
	void SetWave(int wave);

	UFUNCTION()
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TXTSphereCount{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TXTScore{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TXTWave{};
};
