// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Public/Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto PossessedTank = GetControlledTank();
	if (!PossessedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not possessing a tank!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Possessing %s"), *PossessedTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() const
{
	// If we don't have a controlled tank, return.
	if (!GetControlledTank()) return;

	FVector HitLocation; // OUT parameter
	if(GetSightRayHitLocation(OUT HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY);
	
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	FVector LookDirection;

	if(GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(LookDirection, OUT OutHitLocation);
	}

	// Line trace along that look direction, and see what we hit (up to a max range)
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraLocation; // To be discarded
	// "De-project" the screen position of the crosshair to a world direction
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OUT CameraLocation, OUT LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	
	if(GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else
	{
		HitLocation = FVector(0.0f);
		return false;
	}
}
