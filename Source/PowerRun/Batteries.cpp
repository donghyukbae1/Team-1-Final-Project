// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerRun.h"
#include "Batteries.h"


// Sets default values
ABatteries::ABatteries()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABatteries::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABatteries::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

