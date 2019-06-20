// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSCharacter.h"
#include "Engine/World.h"
#include "FPSGameMode.h"


// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{

	/**
	 * Create a Box component called OverlapComponent
	 * Set the collision of the overlapComponent
	 * Set the extent of the Box (x, y and z, in units)
	 * Make OverlapComponent the Root component
	 */
	OverlapComponent = CreateAbstractDefaultSubobject < UBoxComponent>(TEXT("OverlapComponent"));
	OverlapComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComponent->SetBoxExtent(FVector(200.f));
	RootComponent = OverlapComponent;

	OverlapComponent->SetHiddenInGame(false);

	/** Notify OverlapComponent when its overlapped */
	OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);

	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));
	DecalComponent->DecalSize = FVector(200.f, 200.f, 200.f);
	DecalComponent->SetupAttachment(RootComponent);
}


void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("Overlapped with extraction zone!"));

	/**
	 * Cast Extraction Zone to FPSCharacter
	 * check if MyPawn is null and if its carrying objective
	 */
	AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);

	if (MyPawn && MyPawn->bIsCarryingObjective)
	{
		/**
		 * Cast AuthGameMode to FPSGameMode (GetAuthGameMode returns the current GameMode instance, which is always valid during gameplay on the server. GetAuthGameMode is only valid when called in a server; returns null when called on a client).
		 * Check for the nullability of GameMode and call the CompleteMission function.
		 */
		AFPSGameMode* GameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->CompleteMission(MyPawn);
		}
	}
}


