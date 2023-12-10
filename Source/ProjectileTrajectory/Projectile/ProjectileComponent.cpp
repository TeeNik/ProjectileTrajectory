// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileComponent.h"

UProjectileComponent::UProjectileComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UProjectileComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UProjectileComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bThrown)
	{
		Progress += DeltaTime * Speed;
		Progress = FMath::Min(1.0f, Progress);
		const float MovementCurveValue = MovementCurve.GetRichCurveConst()->Eval(Progress);
		FVector FinalPos = FMath::Lerp(StartLocation, TargetLocation, Progress);
		FinalPos.Z += MovementCurveValue * HeightOffset;
		GetOwner()->SetActorLocation(FinalPos);

		if (Progress >= 1.0f)
		{
			bThrown = false;
		}
	}
}

void UProjectileComponent::Throw(const FVector& NewTargetLocation)
{
	StartLocation = GetOwner()->GetActorLocation();
	TargetLocation = NewTargetLocation;
	bThrown = true;
	Progress = 0.0f;
}
