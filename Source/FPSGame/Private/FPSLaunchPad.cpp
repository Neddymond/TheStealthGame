// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSLaunchPad.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
	/**
	 * Create a Box component -> LaunchPad
	 * Set the collision of the launchpad
	 * Set the Box Extent of the LaunchPad
	 * Make the LaunchPad The Root component
	 */
	LaunchPad = CreateDefaultSubobject<UBoxComponent>(TEXT("LaunchPad"));
	LaunchPad->SetBoxExtent(FVector(75, 75, 50));
	RootComponent = LaunchPad;

	/** 
	 * Create a static component -> MeshComp
	*  Attach to RootComponent
	*/
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	/** Launch player when he overlaps the LaunchPad */
	LaunchPad->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::LaunchPlayer);

	LaunchStrength = 1500;
	LaunchPitchAngle = 50.f;
}

/**
 * LaunchPlayer when the player overlaps the LaunchPad
 */
void AFPSLaunchPad::LaunchPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	/** Make Rotator with our specified 'pitch' and convert to a direction Vector * intensity */
	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch = LaunchPitchAngle;
	FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

	ACharacter* player = Cast<ACharacter>(OtherActor);

	if (player)
	{
		/** Launch player; Both boolean gives consistent launch velocity by ignoring the player current location */
		player->LaunchCharacter(LaunchVelocity, true, true);

		/** Spawn Effect */
		UGameplayStatics::SpawnEmitterAtLocation(this, LaunchPadEffects, GetActorLocation());
	}
	/** Did not overlap a player, so check if its a physics simulating actor we can overlap */
	else if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);

		/** Spawn Effects */
		UGameplayStatics::SpawnEmitterAtLocation(this, LaunchPadEffects, GetActorLocation());
	}
}


