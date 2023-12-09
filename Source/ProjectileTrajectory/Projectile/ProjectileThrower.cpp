// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileThrower.h"

AProjectileThrower::AProjectileThrower()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectileThrower::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectileThrower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
