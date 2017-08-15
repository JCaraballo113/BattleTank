// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * Responsible for helping the player aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimCompRef);
private:
	UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 10000000.0f;

	virtual void SetPawn(APawn* InPawn) override;
	void AimTowardsCrosshair() const;
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& WorldDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UFUNCTION()
	void OnTankDeath();
};
