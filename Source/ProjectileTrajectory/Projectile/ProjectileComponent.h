// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectileComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTILETRAJECTORY_API UProjectileComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UProjectileComponent();

	UFUNCTION(BlueprintCallable)
	void Throw(const FVector& NewTargetLocation);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FRuntimeFloatCurve MovementCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Speed = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float HeightOffset = 50.0f;

	FVector StartLocation;
	FVector TargetLocation;
	bool bThrown = false;
	float Progress = 0.0f;
};
