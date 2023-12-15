// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileThrower.h"

#include "AITypes.h"
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
			if (const AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, GetActorTransform()))
			{
				if (auto* Movement = Projectile->FindComponentByClass<UProjectileMovementComponent>())
				{
					const FVector StartLoc = GetActorLocation();
					const FVector TargetLoc = TargetPlayer->GetActorLocation() + FVector::UpVector * TargetFootOffset;

					const FVector Velocity = SuggestProjectileSpeed(StartLoc, TargetLoc, 0.5f, 0.4f, 0.6f, 20, 20);
					Movement->Velocity = Velocity;
					OnProjectileThrown(GetActorLocation(), StartLoc, Velocity);
				}
			}
		}
	}
}

FVector AProjectileThrower::SuggestProjectileSpeed(const FVector& StartPos, const FVector& TargetPos, float ArcParam,
	float AboveArcParam, float BelowArcParam, float AboveAngleThreshold, float BelowAngleThreshold, float GravityOverride, bool DrawDebug)
{
	FVector DirToTarget = TargetPos - StartPos;
	FVector ProjDirToTarget = FVector::VectorPlaneProject(DirToTarget, FVector::UpVector);
	DirToTarget.Normalize();
	ProjDirToTarget.Normalize();

	const float Dot = DirToTarget.Dot(ProjDirToTarget);
	//Vector Up??
	const float HeightDiff = (TargetPos - StartPos).Z;
	const float Angle = (180.0) / UE_DOUBLE_PI * FMath::Acos(Dot);

	if (FMath::Sign(HeightDiff))
	{
		if (Angle > AboveAngleThreshold)
		{
			ArcParam = AboveArcParam;
		}
	}
	else
	{
		if (Angle > BelowAngleThreshold)
		{
			ArcParam = BelowArcParam;
		}
	}

	if (DrawDebug)
	{
		UE_LOG(LogTemp, Log, TEXT("SuggestProjectileSpeed Dot: %f HeightDiff: %f Angle: %f ArcParam: %f"), Dot, HeightDiff, Angle, ArcParam);
		DrawDebugDirectionalArrow(GetWorld(), StartPos, StartPos + DirToTarget * 100.0f, 2, FColor::Red, false, 10);
		DrawDebugDirectionalArrow(GetWorld(), StartPos, StartPos + ProjDirToTarget * 100.0f, 2, FColor::Green, false, 10);
	}

	FVector Velocity = FVector::ZeroVector;
	UGameplayStatics::SuggestProjectileVelocity_CustomArc(GetWorld(), Velocity, StartPos, TargetPos, GravityOverride, ArcParam);
	return Velocity;
}
