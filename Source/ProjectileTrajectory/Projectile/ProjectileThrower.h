// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileThrower.generated.h"

UCLASS()
class PROJECTILETRAJECTORY_API AProjectileThrower : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectileThrower();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = Thrower)
	void OnProjectileThrown(const FVector& Start, const FVector& Target, const FVector& LaunchVelocity);

	UFUNCTION(BlueprintCallable, Category = Thrower)
	FVector SuggestProjectileSpeed(const FVector& StartPos, const FVector& TargetPos, float ArcParam, float AboveArcParam, float BelowArcParam,
		float AboveAngleThreshold, float BelowAngleThreshold, float GravityOverride = 0.0f, bool DrawDebug = false);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Thrower)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Thrower)
	float ThrowPeriod = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Thrower)
	float TargetFootOffset = -50.0f;

	float ThrowTime = 0;
	UPROPERTY(Transient)
	APawn* TargetPlayer;
	bool bInitialized = false;

};
