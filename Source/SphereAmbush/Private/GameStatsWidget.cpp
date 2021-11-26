// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStatsWidget.h"
#include "Components/TextBlock.h"

UGameStatsWidget::UGameStatsWidget(const FObjectInitializer& initializer) : UUserWidget(initializer) {}

void UGameStatsWidget::SetSphereCount(int count)
{
    if (TXTSphereCount)
    {
        auto text = FString::Format(TEXT("Spheres left: {0}"), {count});
        TXTSphereCount->SetText(FText::FromString(text));
        TXTSphereCount->SetVisibility(ESlateVisibility::Visible);
    }
}

void UGameStatsWidget::SetScore(int score)
{
    if (TXTScore)
    {
        auto text = FString::Format(TEXT("Score {0}"), { score });
        TXTScore->SetText(FText::FromString(text));
        TXTScore->SetVisibility(ESlateVisibility::Visible);
    }
}

void UGameStatsWidget::SetWave(int wave)
{
    if (TXTWave)
    {
        auto text = FString::Format(TEXT("Wave {0}"), { wave });
        TXTWave->SetText(FText::FromString(text));
        TXTWave->SetVisibility(ESlateVisibility::Visible);
    }
}

void UGameStatsWidget::NativeConstruct()
{
    Super::NativeConstruct();
}
