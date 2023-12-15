// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileThrower.h"
#include "ProjectileComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
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
				if (auto* Movement = Projectile->FindComponentByClass<UProjectileMovementComponent>())
				{
					const FVector StartLoc = GetActorLocation();
					FVector TargetLoc = TargetPlayer->GetActorLocation() + FVector::UpVector * TargetFootOffset;

					FVector DirToTarget = TargetLoc - StartLoc;
					FVector ProjDirToTarget = FVector::VectorPlaneProject(DirToTarget, FVector::UpVector);
					DirToTarget.Normalize();
					ProjDirToTarget.Normalize();

					DrawDebugDirectionalArrow(GetWorld(), StartLoc, StartLoc + DirToTarget * 100.0f, 2, FColor::Red, false, 10);
					DrawDebugDirectionalArrow(GetWorld(), StartLoc, StartLoc + ProjDirToTarget * 100.0f, 2, FColor::Green, false, 10);
					const float Dot = DirToTarget.Dot(ProjDirToTarget);

					float ArcParam = 0.5f;
					//Vector Up??
					//float HeightDiff = (DirToTarget * FVector::UpVector).Length();
					float HeightDiff = (TargetLoc - StartLoc).Z;
					if (HeightDiff > 200.0f)
					{
						ArcParam -= 0.1f;
					}
					else if (HeightDiff < -200.0f)
					{
						ArcParam += 0.1f;
					}

					UE_LOG(LogTemp, Log, TEXT("Dot: %f Arc: %f HeightDiff: %f"), Dot, ArcParam, HeightDiff);

					FVector Velocity;
					UGameplayStatics::SuggestProjectileVelocity_CustomArc(GetWorld(), Velocity, StartLoc, TargetLoc, 0, ArcParam);

					Movement->Velocity = Velocity;
					OnProjectileThrown(GetActorLocation(), StartLoc, Velocity);
				}

				//if (UProjectileComponent* ProjectileComponent = Projectile->FindComponentByClass<UProjectileComponent>())
				//{
				//
				//	FVector DirToTarget = TargetLoc - GetActorLocation();
				//	float Length = DirToTarget.Length();
				//	DirToTarget.Z = 0;
				//	DirToTarget.Normalize();
				//	TargetLoc += DirToTarget * 150.0f;
				//
				//	ProjectileComponent->Throw(TargetLoc);
				//
				//	float time = 1.0f;
				//	FVector LaunchVel = DirToTarget * (Length + 150) / time;
				//	LaunchVel.Z += 980.0f * time / 2.0f;
				//
				//	OnProjectileThrown(GetActorLocation(), TargetLoc, LaunchVel);
				//}
			}
		}
	}
}
