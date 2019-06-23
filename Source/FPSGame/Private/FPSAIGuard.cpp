// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/GameEngine.h"
#include "FPSGameMode.h"


// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));

	/** Initialize the GuardState */
	GuardState = EAIState::Idle;
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();

	OriginalRotation = GetActorRotation();

	/** Bind to Events */
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);
}

/** Event that happens when we see a pawn */
void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		return;
	}

	//FString message = TEXT("Saw Actor ") + SeenPawn->GetName();
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);

	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);

	/** Game over once we are seen by the Guard */
	AFPSGameMode* GameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->CompleteMission(SeenPawn, false);
	}

	SetGuardState(EAIState::Alerted);
}

/** Event that occurs when a noise is heard by the  Actor*/
void AFPSAIGuard::OnNoiseHeard(APawn* Noiseinstigator, const FVector& Location, float Volume)
{
	/** OnNoiseheard, the player is meant to be suspicious not alerted, so if Guard's State is Alerted, return */
	if (GuardState == EAIState::Alerted)
	{
		return;
	}

	DrawDebugSphere(GetWorld(), Location, 32.f, 12, FColor::Green, false, 10.f);

	/** convert from vector to direction (The direction the AIGuard is meant to look at) */
	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	/** 
	* Rotate the AIGuard to look at the new Direction 
	* The yaw should only be rotated when the the AIGuard looks up
	*/
	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;
	SetActorRotation(NewLookAt);

	/**
	 *	clear Timer to prevent multiple timers running, in case of consecutive call
	 *	Rotate the Guard back to its previous position after a certain amount of time
	 */
	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AFPSAIGuard::ResetOrientation, 3.0f);

	/** Set the GuardState to suspicious when he hears a Noise */
	SetGuardState(EAIState::Suspicious);
}

/** Reposition the guard to its previous position */
void AFPSAIGuard::ResetOrientation()
{
	if (GuardState == EAIState::Alerted)
	{
		return;
	}
	SetActorRotation(OriginalRotation);

	/** Set GuardState to idle once it returns to its original position */
	SetGuardState(EAIState::Idle);
}

/** Set GuardState to NewState if its not the same with the NewState */
void AFPSAIGuard::SetGuardState(EAIState NewState)
{
	if (GuardState == NewState)
	{
		return;
	}

	GuardState = NewState;

	OnStateChanged(GuardState);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



