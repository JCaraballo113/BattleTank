// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto AITank = GetControlledAITank();

	if (!AITank) { return; }
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Possessed AI Tank %s "), *AITank->GetName());
	}
}

ATank* ATankAIController::GetControlledAITank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if(!PlayerPawn) { return nullptr; }
	
	return Cast<ATank>(PlayerPawn);
}

