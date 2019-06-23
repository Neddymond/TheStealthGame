// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

/** Disables input for any player that completes the mission */
void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess)
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);

		if (SpectatingViewpoint)
		{
			/** Array of actors of the specified class to be outputted */
			TArray<AActor*>ReturnedActors;

			/** Find all Actors in the world of the specified class */
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpoint, ReturnedActors);

			if (ReturnedActors.Num() > 0)
			{
				/**
				 * Param NewViewTarget -> Actor to set as view target
				 * Add the first returned Actor to the NewViewTarget
				 */
				AActor* NewViewTarget = ReturnedActors[0];

				/** Change view of the camera on CompleteMission */
				APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
				if (PC)
				{
					PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is nullptr. Please update GameMode with valid subclass. Cannot change Spectating view target"));
		}
	}

	/** Blueprint Implemented function */
	OnMissionCompleted(InstigatorPawn, bMissionSuccess);
}

