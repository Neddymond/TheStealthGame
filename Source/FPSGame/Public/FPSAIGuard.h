// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Allows Actors to see/hear Pawns in the world */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UPawnSensingComponent* PawnSensingComponent;

	/** Called When a pawn is seen */
	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);
	/** Called a when a noise is heard */
	UFUNCTION()
	void OnNoiseHeard(APawn* Noiseinstigator, const FVector& Location, float Volume);

	UFUNCTION()
	void ResetOrientation();

	/** Original position the Guard was facing */
	FRotator OriginalRotation;

	FTimerHandle TimerHandle_ResetOrientation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
};
