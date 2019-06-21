// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPad.generated.h"

class UBoxComponent;

UCLASS()
class FPSGAME_API AFPSLaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSLaunchPad();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MeshComp")
		UStaticMeshComponent* MeshComp;

	/** Pad responsible for launching players */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		UBoxComponent* LaunchPad;

	/** Launch player when he overlaps the launchpad  */
	UFUNCTION()
	void LaunchPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "LaunchPad")
		float LaunchPitchAngle;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "LaunchPad")
		float LaunchStrength;

	/** Particle to emit */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
		UParticleSystem* LaunchPadEffects;
	
};
