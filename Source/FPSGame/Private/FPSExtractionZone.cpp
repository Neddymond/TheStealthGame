// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"


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
}


