// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "TestParClass.h"
#include "Cannon.h"
#include "CoreMinimal.h"
#include "DamageTaker.h"
#include "HealthComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ForceFeedbackEffect.h"
#include "Particles/ParticleSystemComponent.h"
#include <Components/WidgetComponent.h>
#include <Tankogeddon/HP_Bar_Comp.h>
#include "InventoryComponent.h" 
#include <Tankogeddon/InventoryManagerComponent.h>
#include "EquipInventoryComponent.h"
#include "TankPawn.generated.h"



class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class ATankPlayerController;
class ACannon;
class ATargetPoint;
class UHP_Bar_Comp;

UCLASS()
class TANKOGEDDON_API ATankPawn : public APawn, public IDamageTaker, public IEquipInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPawn();

	UFUNCTION()
		void MoveForward(float AxisValue);
	UFUNCTION()
		void MoveLeft(float AxisValue);
	UFUNCTION()
		void RotateRight(float AxisValue);
	UFUNCTION()
		void Fire();
	UFUNCTION()
		void FireSpecial();
	UFUNCTION()
		void ChangeCannon();

	UFUNCTION()
		void TakeDamage(FDamageData DamageData);

	void SetupCannon(TSubclassOf<ACannon> cannonClass);

	UFUNCTION()
		float GetMovementAccuracy() { return MovementAccuracy; };
	UFUNCTION()
		TArray <FVector> GetPatrollingPoints();

	void SetPatrollingPoints(TArray<ATargetPoint*> NewPatrollingPoints);

	UFUNCTION()
		FVector GetTurretForwardVector();

	UFUNCTION()
		void RotateTurretTo(FVector TargetPosition);

	FVector GetEyesPosition();
	ACannon* GetCannon() { return Cannon; };
	UHealthComponent* GetHealthComponent() { return HealthComponent; };
	UInventoryManagerComponent* GetInventoryManager() { return InventoryManagerComponent; };
	UInventoryComponent* GetInventoryComponent() { return InventoryComponent; };
	UEquipInventoryComponent* GetEquipInventoryComponent() { return EquipmentInventoryComponent; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MovementSpeed = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float RotationSpeed = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float InterpolationKey = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret | Speed")
		float TurretRotationInterpolationKey = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret | Cannon")
		TSubclassOf<ACannon> CannonClass;

	float TargetForwardAxisValue;
	float TargetLeftAxisValue;
	float TargetRightAxisValue;
	float CurrentRightAxisValue;

	UPROPERTY()
	ATankPlayerController* TankController;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* CanonSetupPoint;
	
	UPROPERTY()
		ACannon* Cannon;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UWidgetComponent* WidgComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UHP_Bar_Comp* HealthBar;
		


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* DieEffect;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Audio Components")
		UAudioComponent* AudioDieEffect;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Audio Components")
		UAudioComponent* AudioHitEffect;

	UFUNCTION()
		void Die();
	UFUNCTION()
		void DamageTaked(float DamageValue);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Move params | Patrol points", Meta = (MakeEditWidget = true))
		TArray<ATargetPoint*> PatrollingPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Move params | Accuracy")
		float MovementAccuracy = 50;


	UPROPERTY(EditDefaultsOnly)
		UInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly)
		UInventoryManagerComponent* InventoryManagerComponent;

	UPROPERTY(EditDefaultsOnly)
		UEquipInventoryComponent* EquipmentInventoryComponent;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Inventory Slots")
		UStaticMeshComponent* BodySlot;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Inventory Slots")
		UStaticMeshComponent* TurretSlot;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Inventory Slots")
		UStaticMeshComponent* CanonSlot;

	virtual void EquipItem(EEquipSlot Slot, FName ItemId) override;

	virtual void UnequipItem(EEquipSlot Slot, FName ItedId) override;

	UStaticMeshComponent* GetEquipComponent(EEquipSlot EquipSlot);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
