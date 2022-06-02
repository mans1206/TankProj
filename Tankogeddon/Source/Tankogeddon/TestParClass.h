//#pragma once
//
//#include "DamageTaker.h"
//#include "HealthComponent.h"
//#include "Components/BoxComponent.h"
//#include "Components/ArrowComponent.h"
//#include "GameFramework/Actor.h"
//#include "CoreMinimal.h"
//#include "GameFramework/Pawn.h"
//#include <Runtime/Engine/Classes/GameFramework/SpringArmComponent.h>
//#include <Runtime/Engine/Classes/Camera/CameraComponent.h>
//#include <Tankogeddon/Cannon.h>
////#include "TestParClass.generated.h"
//
//UCLASS()
//class TANKOGEDDON_API TestParClass : public APawn, public IDamageTaker
//{
//	GENERATED_BODY()
//
//public:
//	// Sets default values for this pawn's properties
//	TestParClass();
//
//	virtual void SetupCannon(TSubclassOf<ACannon> cannonClass) = 0;
//
//
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
//		UStaticMeshComponent* BodyMesh;
//	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
//		UStaticMeshComponent* TurretMesh;
//
//	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
//		UArrowComponent* CannonSetupPoint;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
//		TSubclassOf<ACannon> CannonClass;
//
//	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
//		UBoxComponent* HitCollider;
//	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
//		UHealthComponent* HealthComponent;
//
//	UPROPERTY()
//		ACannon* Cannon;
//
//	UFUNCTION()
//		virtual void Die() = 0;
//	UFUNCTION()
//		virtual void DamageTaked(float DamageValue) = 0;
//
//	UFUNCTION()
//		virtual void TakeDamage(FDamageData DamageData) = 0;
//
//public:
//
//	virtual void Fire() = 0;
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//	// Called to bind functionality to input
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
//
//};
//
