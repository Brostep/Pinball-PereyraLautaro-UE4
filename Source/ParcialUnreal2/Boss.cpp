// Fill out your copyright notice in the Description page of Project Settings.

#include "Boss.h"


// Sets default values
ABoss::ABoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Register Events
	_collision = CreateDefaultSubobject<USphereComponent>(TEXT("RootCollision"));
	_collision->SetSphereRadius(120);
	_collision-> OnComponentBeginOverlap.AddDynamic(this, &ABoss::BeginOverlap);
}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();
	myMaterial = UMaterialInstanceDynamic::Create(matInterface, this);
	UStaticMeshComponent* myMesh = FindComponentByClass<UStaticMeshComponent>();
	if (myMesh && myMaterial)
	{
		myMesh->SetMaterial(0, myMaterial);
		FVector green = FVector(0, 1.f, 0.0f);
		myMaterial->SetVectorParameterValue("Hit", green);
		MaterialSetted = true;
	}
	
	audioComp = FindComponentByClass<UAudioComponent>();
}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Overlaping = false;
	if (MaterialSetted == false && Overlaping == false)
	{
		if (myMaterial)
		{
			FVector green = FVector(0, 1.f, 0.0f);
			myMaterial->SetVectorParameterValue("Hit", green);
		}
	}
}

void ABoss::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult &SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		if (myMaterial)
		{
			MaterialSetted = false;
			Overlaping = true;
			FVector red = FVector(1, 0.0f, 0.0f);
			myMaterial->SetVectorParameterValue("Hit", red);
		}
		if (audioComp)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "PLAY SONG");
			audioComp->Stop();
			audioComp->Sound = bossHit;
			audioComp->Play();
		}
	}
}