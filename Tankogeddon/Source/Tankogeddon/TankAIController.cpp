// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
	
}

void ATankAIController::Initialize()
{
	TankPawn = Cast <ATankPawn>(GetPawn());

	if (TankPawn)
	{
		PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		FVector pawnLocation = TankPawn->GetActorLocation();
		MovementAccuracy = TankPawn->GetMovementAccuracy();
		TArray<FVector> points = TankPawn->GetPatrollingPoints();

		for (FVector point : points)
		{
			PatrollingPoints.Add(point);
		}
		CurrentPatrolPointIndex = 0;
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TankPawn)
		Initialize();

	if (!TankPawn)
		return;

	//TankPawn->MoveForward(1);

	FVector currentPoint = PatrollingPoints[CurrentPatrolPointIndex];
	FVector pawnLocation = TankPawn->GetActorLocation();
	if (FVector::Distance(currentPoint, pawnLocation) <= MovementAccuracy)
	{
		CurrentPatrolPointIndex++;
		if (CurrentPatrolPointIndex >= PatrollingPoints.Num())
		{
			CurrentPatrolPointIndex = 0;
		}
	}
	FVector moveDirection = currentPoint - pawnLocation;
	moveDirection.Normalize();
	FVector forwardDirection = TankPawn->GetActorForwardVector();
	FVector rightDirection = TankPawn->GetActorRightVector();

	DrawDebugLine(GetWorld(), pawnLocation, currentPoint, FColor::Blue, false, 0.1f, 0, 5);

	float forwardAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(forwardDirection, moveDirection)));
	float rightAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(rightDirection, moveDirection)));

	float rotationValue = 0;
	if (forwardAngle > 5)
	{
		rotationValue = 1;
	}
	if (rightAngle > 90)
	{
		rotationValue = -rotationValue;
	}
	//UE_LOG(LogTemp, Warning, TEXT("AI Rotation forwardAngle: %f rightAngle: %f rotationValue:% f"), forwardAngle, rightAngle, rotationValue);
	TankPawn->RotateRight(rotationValue);

	Targeting();

}


void ATankAIController::Targeting()
{
	if (CanFire())
	{
		Fire();
	}
	else
	{
		RotateToPlayer();
	}
}

void ATankAIController::RotateToPlayer()
{
	if (IsPlayerInRange())
	{
		TankPawn->RotateTurretTo(PlayerPawn->GetActorLocation());
	}
}

bool ATankAIController::IsPlayerInRange()
{
	return FVector::Distance(TankPawn->GetActorLocation(), PlayerPawn->GetActorLocation()) <= TargetingRange;
}

void ATankAIController::Fire()
{
	TankPawn->Fire();
}

bool ATankAIController::CanFire()
{
	if (!IsPlayerSeen())
		return false;

	FVector targetingDir = TankPawn->GetTurretForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - TankPawn->GetActorLocation();
	dirToPlayer.Normalize();
	float aimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir, dirToPlayer)));
	return aimAngle <= Accuracy;
}

bool ATankAIController::IsPlayerSeen()
{
	if (!PlayerPawn)
		Initialize();

	FVector playerPos = PlayerPawn->GetActorLocation();
	FVector eyesPos = TankPawn->GetEyesPosition();
	FHitResult hitResult;
	FCollisionQueryParams traceParams =	FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
	traceParams.bTraceComplex = true;
	traceParams.AddIgnoredActor(TankPawn);
	traceParams.bReturnPhysicalMaterial = false;
	if (GetWorld()->LineTraceSingleByChannel(hitResult, eyesPos, playerPos,	ECollisionChannel::ECC_Visibility, traceParams))
	{
		if (hitResult.Actor.Get())
		{
			//DrawDebugLine(GetWorld(), eyesPos, hitResult.Location, FColor::Cyan, false, 0.5f, 0, 10);
			return hitResult.Actor.Get() == PlayerPawn;
		}
	}
	DrawDebugLine(GetWorld(), eyesPos, playerPos, FColor::Cyan, false, 0.5f, 0, 10);
	return false;
}