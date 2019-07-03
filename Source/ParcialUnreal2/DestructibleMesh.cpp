// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructibleMesh.h"


// Sets default values
ADestructibleMesh::ADestructibleMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADestructibleMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestructibleMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

