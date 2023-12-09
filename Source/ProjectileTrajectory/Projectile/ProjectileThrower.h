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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Thrower)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Thrower)
	float ThrowPeriod = 5.0f;

	float ThrowTime = 0;

	UPROPERTY(Transient)
	ACharacter* TargetPlayer;

};
