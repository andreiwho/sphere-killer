// Copyright Epic Games, Inc. All Rights Reserved.

#include "SphereAmbushHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"

ASphereAmbushHUD::ASphereAmbushHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;
}


void ASphereAmbushHUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw very simple crosshair
	{
		// find center of the Canvas
		const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);


		// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
		const FVector2D CrosshairDrawPosition((Center.X),
											  (Center.Y + 20.0f));

		// draw the crosshair
		FCanvasTileItem TileItem(CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
		TileItem.BlendMode = SE_BLEND_Translucent;
		Canvas->DrawItem(TileItem);
	}

}

void ASphereAmbushHUD::BeginPlay()
{
	Super::BeginPlay();

	if (GameStatsClass)
	{
		GameStats = CreateWidget<UGameStatsWidget>(GetWorld(), GameStatsClass);

		if (GameStats)
		{
			GameStats->AddToViewport();
		}
	}
}

void ASphereAmbushHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASphereAmbushHUD::SetSphereCount(int count)
{
	if (GameStats)
	{
		GameStats->SetSphereCount(count);
	}
}

void ASphereAmbushHUD::SetScore(int score)
{
	if (GameStats)
	{
		GameStats->SetScore(score);
	}
}

void ASphereAmbushHUD::SetWave(int wave)
{
	if (GameStats)
	{
		GameStats->SetWave(wave);
	}
}
