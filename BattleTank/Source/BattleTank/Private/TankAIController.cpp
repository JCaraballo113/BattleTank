// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Public/TankAimingComponent.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossesedTank = Cast<ATank>(InPawn);

		if (!ensure(PossesedTank)) { return; }

		// Subscribe our local method to the Tank's death event
		PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
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

	if (AIAimComp->GetFiringState() == EFiringState::Locked)
	{
		AIAimComp->Fire();
	}
}

void ATankAIController::OnTankDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

