// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Public/TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AITank = GetPawn();

	if (!ensure(PlayerTank && AITank)) { return; }

	auto AIAimComp = AITank->FindComponentByClass<UTankAimingComponent>();
	// Move towards Actor
	MoveToActor(PlayerTank, AcceptanceRadius);
	// Aim towards the player
	AIAimComp->AimAt(PlayerTank->GetActorLocation());
	AIAimComp->Fire();
}

