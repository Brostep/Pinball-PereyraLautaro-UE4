// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
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
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* skull;

	bool Overlaping;
	bool MaterialSetted;
	bool debuffOn;

	UPROPERTY(EditAnywhere)
		float timerToDebufSlowGame;
	UPROPERTY(EditAnywhere)
		float debufDuration;
	UPROPERTY(EditAnywhere)
		float slowGameSpeed;
	UPROPERTY(EditAnywhere)
		float timerToDebufMultiplier;
	UPROPERTY(EditAnywhere)
		float debufDurationMultiplier;
	UPROPERTY(EditAnywhere)
		AActor* debufLeft;
	UPROPERTY(EditAnywhere)
		AActor* debufRight;
	
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
	UFUNCTION()
		void slowSpeedDebuff();	
	UFUNCTION()
		void slowSpeedDebuffFinish();
	UFUNCTION()
		void setOnDebuffMultiplier();
	UFUNCTION()
		void setOffDebufMultiplier();
};
