// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankPawn.h"
#include "DamageTaker.h"
#include "Engine/TargetPoint.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ForceFeedbackEffect.h"
#include "Particles/ParticleSystemComponent.h"
#include "MapLoader.h"
#include "TankFactory.generated.h"


class AMapLoader;


UCLASS()
class TANKOGEDDON_API ATankFactory : public AActor, public IDamageTaker
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATankFactory();
	UFUNCTION()
		virtual void TakeDamage(FDamageData DamageData) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn tanks params")
		AMapLoader* LinkedMapLoader;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SpawnNewTank();

	UFUNCTION()
		void Die();

	UFUNCTION()
		void DamageTaked(float DamageValue);


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BuildingMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* TankSpawnPoint;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn tanks params")
		TSubclassOf<ATankPawn> SpawnTankClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn tanks params")
		float SpawnTankRate = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn tanks params")
		TArray<ATargetPoint*> TankWayPoints;


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UParticleSystemComponent* DieEffect;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Audio Components")
		UAudioComponent* AudioSpawnEffect;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Audio Components")
		UAudioComponent* AudioDieEffect;
};
