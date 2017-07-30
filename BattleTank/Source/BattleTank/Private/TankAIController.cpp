// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Public/Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto AITank = GetControlledAITank();

	if (AITank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Possessed AI Tank %s "), *AITank->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GetPlayerTank())
	{
		GetControlledAITank()->AimAt(GetPlayerTank()->GetActorLocation());
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

