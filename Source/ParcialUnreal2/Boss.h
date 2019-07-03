// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Boss.generated.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)

UCLASS()
class PARCIALUNREAL2_API ABoss : public AActor
{
	GENERATED_BODY()
	
public:	
	ABoss();

	UPROPERTY(EditAnywhere)
		UMaterialInterface* matInterface;

	UMaterialInstanceDynamic* myMaterial;

	UAudioComponent* audioComp;

	UPROPERTY(EditAnywhere)
		USoundWave* bossHit;	

	USphereComponent* _collision;

	bool Overlaping;
	bool MaterialSetted;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);
};
