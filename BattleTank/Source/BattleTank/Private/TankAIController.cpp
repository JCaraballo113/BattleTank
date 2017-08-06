// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Public/Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto AITank = Cast<ATank>(GetPawn());

	if(PlayerTank)
	{
		// Move towards Actor
		MoveToActor(PlayerTank, AcceptanceRadius);
		// Aim towards the player
		AITank->AimAt(PlayerTank->GetActorLocation());
		
		AITank->Fire();
	}
}

