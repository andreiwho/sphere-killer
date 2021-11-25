// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStatsWidget.h"
#include "Components/TextBlock.h"


UGameStatsWidget::UGameStatsWidget(const FObjectInitializer& initializer) 
    : UUserWidget(initializer)
{

}


void UGameStatsWidget::UpdateInnerSphereCount(int count)
{
    
    if (TXTInnerSphereCount)
    {
        // Turn on
        if (TXTInnerSphereCount->Visibility == ESlateVisibility::Hidden)
        {
            TXTInnerSphereCount->SetVisibility(ESlateVisibility::Visible);
        }

        // Set the text
        TXTInnerSphereCount->SetText(FText::FromString(FString::FromInt(count)));
    }
}


void UGameStatsWidget::NativeConstruct()
{
    Super::NativeConstruct();
}
