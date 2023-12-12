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
					FVector TargetLoc = TargetPlayer->GetActorLocation() + FVector::UpVector * TargetFootOffset;

					FVector DirToTarget = TargetLoc - GetActorLocation();
					float Length = DirToTarget.Length();
					DirToTarget.Z = 0;
					DirToTarget.Normalize();
					TargetLoc += DirToTarget * 150.0f;

					ProjectileComponent->Throw(TargetLoc);

					float time = 1.0f;
					FVector LaunchVel = DirToTarget * (Length + 150) / time;
					LaunchVel.Z += 980.0f * time / 2.0f;

					OnProjectileThrown(GetActorLocation(), TargetLoc, LaunchVel);
				}
			}
		}
	}
}
