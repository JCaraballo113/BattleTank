// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank Track is used to set maximum driving force and to apply forces to the tank.
 */
UCLASS(ClassGroup=(Custom), meta=(BluePrintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
	// This is max force per track in Newtons
	UPROPERTY(EditDefaultsOnly, Category = Driving)
	float TrackMaxDrivingForce = 400000; // Assumes 40 ton tank and 1g acceleration

private:
	UTankTrack();
	virtual void BeginPlay() override;

	void ApplySidewaysForce();

	UFUNCTION(BlueprintCallable, Category = "Track Collision")
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	void DriveTrack();

	float CurrentThrottle = 0;
};
