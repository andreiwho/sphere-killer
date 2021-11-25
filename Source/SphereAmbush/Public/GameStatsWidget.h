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

    void UpdateInnerSphereCount(int count);

    virtual void NativeConstruct() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    class UTextBlock* TXTInnerSphereCount{ nullptr };
};
