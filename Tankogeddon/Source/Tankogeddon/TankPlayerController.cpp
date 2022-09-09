// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "DrawDebugHelpers.h"
#include "TankPawn.h"


ATankPlayerController::ATankPlayerController()
{
	bShowMouseCursor = true;
	//PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &ATankPlayerController::MoveForward);
	InputComponent->BindAxis("MoveLeft", this, &ATankPlayerController::MoveLeft);
	InputComponent->BindAxis("RotateRight", this, &ATankPlayerController::RotateRight);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ATankPlayerController::Fire);
	InputComponent->BindAction("FireSpecial", IE_Pressed, this, &ATankPlayerController::FireSpecial);
	InputComponent->BindAction("ChangeCannon", IE_Pressed, this, &ATankPlayerController::ChangeCannon);
	InputComponent->BindKey(EKeys::LeftMouseButton, IE_Released, this, &ATankPlayerController::OnLeftMouseButtonUp);
	InputComponent->BindAction("Open_Inventory", IE_Pressed, this, &ATankPlayerController::OpenInventory);
	InputComponent->BindAction("OpenEquipInventory", IE_Pressed, this, &ATankPlayerController::OpenEquipInventory);
}

void ATankPlayerController::OpenInventory()
{
	TankPawn->GetInventoryManager()->Init(TankPawn->GetInventoryComponent());
}

void ATankPlayerController::OpenEquipInventory()
{
	TankPawn->GetInventoryManager()->InitEquipment(TankPawn->GetEquipInventoryComponent());
}


void ATankPlayerController::ChangeCannon()
{
	TankPawn->ChangeCannon();
}
void ATankPlayerController::Fire()
{
	TankPawn->Fire();
}

void ATankPlayerController::FireSpecial()
{
	TankPawn->FireSpecial();
}

void ATankPlayerController::OnLeftMouseButtonUp()
{
	OnMouseButtonUp.Broadcast();
}

void ATankPlayerController::BeginPlay()
{
	bEnableClickEvents = true;
	Super::BeginPlay();
	TankPawn = Cast<ATankPawn>(GetPawn());
}

void ATankPlayerController::MoveForward(float AxisValue)
{
	TankPawn->MoveForward(AxisValue);
}


void ATankPlayerController::MoveLeft(float AxisValue)
{
	TankPawn->MoveLeft(AxisValue);
}

void ATankPlayerController::RotateRight(float AxisValue)
{
	TankPawn->RotateRight(AxisValue);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	FVector mouseDirection;
	DeprojectMousePositionToWorld(MousePos, mouseDirection);
	FVector pawnPos = TankPawn->GetActorLocation();
	MousePos.Z = pawnPos.Z;
	FVector dir = MousePos - pawnPos;
	dir.Normalize();
	MousePos = pawnPos + dir * 1000;
	//DrawDebugLine(GetWorld(), pawnPos, MousePos, FColor::Green, false, 0.1f, 0, 5);
}