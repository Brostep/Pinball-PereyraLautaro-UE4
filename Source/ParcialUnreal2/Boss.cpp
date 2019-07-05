// Fill out your copyright notice in the Description page of Project Settings.

#include "Boss.h"


// Sets default values
ABoss::ABoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Register Events
	skull = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube Mesh"));
	_collision = CreateDefaultSubobject<USphereComponent>(TEXT("RootCollision"));
	_collision->SetSphereRadius(0.7f);
	_collision-> OnComponentBeginOverlap.AddDynamic(this, &ABoss::BeginOverlap);

	ConstructorHelpers::FObjectFinder<UStaticMesh> skullMesh(TEXT("StaticMesh'/Game/Assets/Skull.Skull'"));
	if (skullMesh.Object)
		skull->SetStaticMesh(skullMesh.Object);
	if (skull)
	{
		skull->SetRelativeScale3D(FVector(200, 200, 200));

		FRotator Rotation;
		Rotation.Yaw = -180.0f;
		Rotation.Pitch = 0.0f;
		Rotation.Roll = 90.0f;
		
		skull->SetRelativeRotation(Rotation);
	}
}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();
	myMaterial = UMaterialInstanceDynamic::Create(matInterface, this);
	if (skull && myMaterial)
	{
		skull->SetMaterial(0, myMaterial);
		FVector green = FVector(0, 1.f, 0.0f);
		myMaterial->SetVectorParameterValue("Hit", green);
		MaterialSetted = true;
	}
	
	audioComp = FindComponentByClass<UAudioComponent>();
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &ABoss::setOnDebuffMultiplier, timerToDebufMultiplier, false);
	debufLeft->SetActorHiddenInGame(true);
	debufRight->SetActorHiddenInGame(true);

}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Overlaping = false;
	if (MaterialSetted == false && Overlaping == false && debuffOn == false)
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
			FVector white = FVector(0.5f, 0.5f, 0.5f);
			myMaterial->SetVectorParameterValue("Hit", white);
		}
		if (audioComp)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "PLAY SONG");
			audioComp->Stop();
			audioComp->Sound = bossHit;
			audioComp->Play();
		}
		auto triggerPower = FMath::RandRange(1, 100);
		if (triggerPower > 60)
		{
			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(
				UnusedHandle, this, &ABoss::slowSpeedDebuff, timerToDebufSlowGame, false);
		}
	}
}

void ABoss::slowSpeedDebuff()
{
	debuffOn = true;
	FVector red = FVector(1, 0.0f, 0.0f);
	myMaterial->SetVectorParameterValue("Hit", red);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), slowGameSpeed);
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &ABoss::slowSpeedDebuffFinish, debufDuration, false);
}

void ABoss::slowSpeedDebuffFinish()
{
	debuffOn = false;
	FVector green = FVector(0, 1.f, 0.0f);
	myMaterial->SetVectorParameterValue("Hit", green);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);
}
void ABoss::setOnDebuffMultiplier()
{
	auto triggerPower = FMath::RandRange(1, 100);
	if (triggerPower > 20)
	{
		debuffOn = true;
		FVector red = FVector(1, 0.0f, 0.0f);
		myMaterial->SetVectorParameterValue("Hit", red);
		//spawn
		FActorSpawnParameters params = FActorSpawnParameters();

		auto leftORight = FMath::RandRange(1, 10);
		if (leftORight >5)
			debufLeft->SetActorHiddenInGame(false);
		else
			debufRight->SetActorHiddenInGame(false);

		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(
			UnusedHandle, this, &ABoss::setOffDebufMultiplier, debufDurationMultiplier, false);
	}
	else
	{
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(
			UnusedHandle, this, &ABoss::setOnDebuffMultiplier, timerToDebufMultiplier, false);
	}
}
void ABoss::setOffDebufMultiplier()
{

	debufLeft->SetActorHiddenInGame(true);
	debufRight->SetActorHiddenInGame(true);
	//clean
	debuffOn = false;
	FVector green = FVector(0, 1.f, 0.0f);
	myMaterial->SetVectorParameterValue("Hit", green);
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &ABoss::setOnDebuffMultiplier, timerToDebufMultiplier, false);
}