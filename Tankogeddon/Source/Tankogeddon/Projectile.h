// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TANKOGEDDON_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	virtual void Start();
	virtual void Explode();
	bool IsExplode();
	void proverka();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeed = 500;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveRate = 0.005f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
		float Damage = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
		float PushForce = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explode")
		float ExplodeRadius = 50;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explode")
		bool isExplodeEnabled = false;


	FTimerHandle MovementTimerHandle;


	UFUNCTION()
		void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void Move();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
