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
	void Throw(const FVector& TargetLocation);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FRuntimeFloatCurve MovementCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Speed = 10.0f;

};
