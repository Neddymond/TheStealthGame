// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSObjectiveActor.h"
#include "Components/SphereComponent.h"
#include "EngineMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "FPSCharacter.h"

// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
	/** Create a component of type UStaticMeshComponent */
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));

	/**	Set the collision of the MeshComp */
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	/** Make MeshComp the Root component in the hierarchy */
	RootComponent = MeshComp;

	/** Create a component of type USphereComponent */
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));

	/** Set the collision of the SphereComp */
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	/** Attach SphereComp to the RootComponent(MeshComp) */
	SphereComp->SetupAttachment(MeshComp);

}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();

	PlayEffects();
	
}

void AFPSObjectiveActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}

/** Notify an Actor when another Actor overlaps it */
void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	PlayEffects();

	/** Cast OtherACtor to MyCharacter */
	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);

	/**
	 * If MyCharacter is not null
	 *Set it's boolean member 'bIsCarryingObjective' to true
	 */
	if (MyCharacter)
	{
		MyCharacter->bIsCarryingObjective = true;

		Destroy();
	}


}

