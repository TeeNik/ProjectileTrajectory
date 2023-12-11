// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileThrower.h"
#include "ProjectileComponent.h"
#include "Kismet/GameplayStatics.h"

AProjectileThrower::AProjectileThrower()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectileThrower::BeginPlay()
{
	Super::BeginPlay();

	TargetPlayer = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (TargetPlayer && ProjectileClass)
	{
		bInitialized = true;
	}
}

void AProjectileThrower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInitialized)
	{
		ThrowTime += DeltaTime;
		if (ThrowTime >= ThrowPeriod)
		{
			ThrowTime = 0.0f;

			FActorSpawnParameters SpawnParameters;
			const AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, GetActorTransform());
			if (Projectile)
			{
				if (UProjectileComponent* ProjectileComponent = Projectile->FindComponentByClass<UProjectileComponent>())
				{
					ProjectileComponent->Throw(TargetPlayer->GetActorLocation());
				}
			}
		}
	}
}
