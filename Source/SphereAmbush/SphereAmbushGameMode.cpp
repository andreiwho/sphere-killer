// Copyright Epic Games, Inc. All Rights Reserved.

#include "SphereAmbushGameMode.h"
#include "SphereAmbushHUD.h"
#include "SphereAmbushCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASphereAmbushGameMode::ASphereAmbushGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASphereAmbushHUD::StaticClass();
}
