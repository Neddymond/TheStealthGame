// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSExtractionZone.generated.h"

class UBoxComponent;

UCLASS()
class FPSGAME_API AFPSExtractionZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSExtractionZone();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* OverlapComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDecalComponent* DecalComponent;


	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	/** Sound to be played if Objective is missing */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sounds")
	USoundBase* ObjectiveMissingSound;
};
