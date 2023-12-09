// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/ProjectileComponent.h"

// Sets default values for this component's properties
UProjectileComponent::UProjectileComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UProjectileComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UProjectileComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);



}

