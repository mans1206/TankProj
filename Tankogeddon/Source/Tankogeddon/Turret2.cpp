// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret2.h"
#include "TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Cannon.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include <Runtime/Engine/Public/DrawDebugHelpers.h>

// Sets default values
ATurret2::ATurret2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret body"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	TurretMesh->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	CannonSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform);

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(BodyMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	HealthComponent->OnDie.AddUObject(this, &ATurret2::Die);
	HealthComponent->OnDamaged.AddUObject(this, &ATurret2::DamageTaked);

	DieEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Die Effect"));
	DieEffect->SetupAttachment(CannonSetupPoint);

	AudioDieEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Effect"));
	AudioHitEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Hit-Effect"));

	UStaticMesh* turretMeshTemp = LoadObject<UStaticMesh>(this, *TurretMeshPath);
	if (turretMeshTemp)
		TurretMesh->SetStaticMesh(turretMeshTemp);

	UStaticMesh* bodyMeshTemp = LoadObject<UStaticMesh>(this, *BodyMeshPath);
	if (bodyMeshTemp)
		BodyMesh->SetStaticMesh(bodyMeshTemp);



}

// Called when the game starts or when spawned
void ATurret2::BeginPlay()
{
	Super::BeginPlay();
	SetupCannon();
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	FTimerHandle _targetingTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(_targetingTimerHandle, this,	&ATurret2::Targeting, TargetingRate, true, TargetingRate);
}

void ATurret2::SetupCannon()
{
	if (!CannonClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannon class is null"));
		return;
	}
	FActorSpawnParameters params;
	params.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, params);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

}

void ATurret2::Destroyed()
{
	if (Cannon)
	{
		Cannon->Destroy();
	}
}
void ATurret2::Targeting()
{
	if (IsPlayerInRange() && IsPlayerSeen())
	{
		RotateToPlayer();
	}
	if (CanFire() && Cannon && Cannon->IsReadyToFire())
	{
		Fire();
	}
}

void ATurret2::RotateToPlayer()
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerPawn->GetActorLocation());
	FRotator currRotation = TurretMesh->GetComponentRotation();
	targetRotation.Pitch = currRotation.Pitch;
	targetRotation.Roll = currRotation.Roll;
	TurretMesh->SetWorldRotation(FMath::Lerp(currRotation, targetRotation, TargetingSpeed));
}

bool ATurret2::IsPlayerInRange()
{
	return FVector::Distance(PlayerPawn->GetActorLocation(), GetActorLocation()) <= TargetingRange;
}

bool ATurret2::IsPlayerSeen()
{
	FVector playerPos = PlayerPawn->GetActorLocation();
	FVector eyesPos = CannonSetupPoint->GetComponentLocation();
	FHitResult hitResult;
	FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
	traceParams.bTraceComplex = true;
	traceParams.AddIgnoredActor(Cannon);
	traceParams.bReturnPhysicalMaterial = false;
	if (GetWorld()->LineTraceSingleByChannel(hitResult, eyesPos, playerPos, ECollisionChannel::ECC_WorldStatic, traceParams))
	{
		if (hitResult.Actor.Get())
		{
			//DrawDebugLine(GetWorld(), eyesPos, hitResult.Location, FColor::Cyan, false, 0.5f, 0, 10);
			return hitResult.Actor.Get() == PlayerPawn;
		}
	}
	//DrawDebugLine(GetWorld(), eyesPos, playerPos, FColor::Cyan, false, 0.5f, 0, 10);
	return false;
}


bool ATurret2::CanFire()
{
	if (!IsPlayerSeen())
		return false;

	FVector targetingDir = TurretMesh->GetForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
	dirToPlayer.Normalize();
	float aimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDir, dirToPlayer)));
	return aimAngle <= Accuracy;
}

void ATurret2::Fire()
{
	if (IsPlayerInRange() && CanFire())
	{
		Cannon->Fire();
	}
}

void ATurret2::TakeDamage(FDamageData DamageData)
{
	AudioHitEffect->Play();
	HealthComponent->TakeDamage(DamageData);
}

void ATurret2::Die()
{
	Destroy();
	UE_LOG(LogTemp, Warning, TEXT("Turret Died"));
	DieEffect->ActivateSystem();
	AudioDieEffect->Play();
}

void ATurret2::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Turret %s taked damage:%f Health:%f"), *GetName(), DamageValue, HealthComponent->GetHealth());
}