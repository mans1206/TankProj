// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class ATankPawn;

UCLASS()
class TANKOGEDDON_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		ATankPawn* TankPawn;
	UPROPERTY()
		FVector MousePos;

	void Fire();
	void FireSpecial();
	void ChangeCannon();

public:
	ATankPlayerController();
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTine) override;
	FVector GetmousePos() { return MousePos; };
protected:

	virtual void BeginPlay() override;
	void MoveForward(float AxisValue);
	void MoveLeft(float AxisValue);
	void RotateRight(float AxisValue);	
};
