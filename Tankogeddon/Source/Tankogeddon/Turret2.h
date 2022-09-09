
#pragma once

//#include "TestParClass.h"
#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Cannon.h"
#include "DamageTaker.h"
#include "HealthComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ForceFeedbackEffect.h"
#include "Particles/ParticleSystemComponent.h"
#include <Components/WidgetComponent.h>
#include <Tankogeddon/HP_Bar_Comp.h>
#include "Turret2.generated.h"

UCLASS()
class TANKOGEDDON_API ATurret2 : public AActor, public IDamageTaker//, public TestParClass

{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATurret2();

	UFUNCTION()
		void TakeDamage(FDamageData DamageData);

	virtual void PostInitializeComponents() override;


	UFUNCTION()
		void Die();

	UFUNCTION()
		void DamageTaked(float DamageValue);

	bool IsPlayerSeen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	void Targeting();
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool CanFire();
	void Fire();
	void SetupCannon();



protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* CannonSetupPoint;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* DieEffect;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* AudioDieEffect;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UAudioComponent* AudioHitEffect;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UWidgetComponent* WidgComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UHP_Bar_Comp* HealthBar;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		TSubclassOf<ACannon> CannonClass;

	UPROPERTY()
		ACannon* Cannon;
	UPROPERTY()
		APawn* PlayerPawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargetingRange = 1000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargetingSpeed = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargetingRate = 0.005f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float Accuracy = 10;


	const FString BodyMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Tower1.SM_CSC_Tower1'";
	const FString TurretMeshPath = "StaticMesh'/Game/CSC/Meshes/SM_CSC_Gun1.SM_CSC_Gun1'";

};

