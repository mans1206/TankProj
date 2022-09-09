// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include <Runtime/Engine/Public/DrawDebugHelpers.h>
#include <Tankogeddon/ReallyAmmoBox.h>
#include <Tankogeddon/DamageTaker.h>
#include <Tankogeddon/TankPawn.h>
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon Mesh"));
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);

	ShootEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Shoot Effect"));
	ShootEffect->SetupAttachment(ProjectileSpawnPoint);

	AudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Effect"));
	
}

void ACannon::SetAmmo(float NewAmmo)
{
	Ammo = NewAmmo;
}

void ACannon::Fire()
{

	if (!ReadyToFire)
	{
		return;
	}
	ReadyToFire = false;


		ShootEffect->ActivateSystem();
		AudioEffect->Play();

		if (GetOwner() && GetOwner() == GetWorld()->GetFirstPlayerController()->GetPawn())
		{
			if (ShootForceEffect)
			{
				FForceFeedbackParameters shootForceEffectParams;
				shootForceEffectParams.bLooping = false;
				shootForceEffectParams.Tag = "shootForceEffectParams";
				GetWorld()->GetFirstPlayerController()->ClientPlayForceFeedback(ShootForceEffect, shootForceEffectParams);
			}
		}

		if (Type == ECannonType::FireProjectile)
		{
			GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, FString::Printf(TEXT("Fire - projectile, Ammo: %f"), Ammo));

			AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(),
				ProjectileSpawnPoint->GetComponentRotation());
			if (projectile)
			{
				projectile->Start();
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - trace");
			FHitResult hitResult;
			FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
			traceParams.bTraceComplex = true;
			traceParams.bReturnPhysicalMaterial = false;

			FVector start = ProjectileSpawnPoint->GetComponentLocation();
			FVector end = ProjectileSpawnPoint->GetForwardVector() * FireRange + start;

			if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_WorldStatic, traceParams))
			{
				DrawDebugLine(GetWorld(), start, hitResult.Location, FColor::Red, false, 0.5f, 0, 5);
				if (hitResult.Actor.Get())
				{
					UE_LOG(LogTemp, Warning, TEXT("Lazer collided with %s. "), *hitResult.Actor.Get()->GetName());
					AActor* owner = GetOwner();
					AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;
					if (hitResult.Actor.Get() != owner && hitResult.Actor.Get() != ownerByOwner)
					{
						IDamageTaker* damageTakerActor = Cast<IDamageTaker>(hitResult.Actor.Get());
						if (damageTakerActor)
						{
							FDamageData damageData;
							damageData.DamageValue = 1;
							damageData.Instigator = owner;
							damageData.DamageMaker = this;

							damageTakerActor->TakeDamage(damageData);
						}
						else
						{
							hitResult.Actor.Get()->Destroy();
						}
					}

				}
			}
			else
			{
				DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 0.5f, 0, 5);
			}
	}

	
	Ammo--;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
}
void ACannon::Fireproj()
{
	AProjectile* projectile1 = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(),
		ProjectileSpawnPoint->GetComponentRotation());
	if (projectile1)
	{
		projectile1->Start();
	}
}


void ACannon::FireSpecial()
{
	if (Ammo / 3 >= 1)
	{
		if (!ReadyToFire)
		{
			return;
		}
		ReadyToFire = false;

		FireDamage += 2;
		Reload();

		if (Type == ECannonType::FireProjectile)
		{
			GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, FString::Printf(TEXT("Fire - projectile, Ammo: %f"), Ammo));

			AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(),
				ProjectileSpawnPoint->GetComponentRotation());
			if (projectile)
			{
				projectile->Start();
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - trace");
			FHitResult hitResult;
			FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
			traceParams.bTraceComplex = true;
			traceParams.bReturnPhysicalMaterial = false;

			FVector start = ProjectileSpawnPoint->GetComponentLocation();
			FVector end = ProjectileSpawnPoint->GetForwardVector() * FireRange + start;

			if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_WorldStatic, traceParams))
			{
				DrawDebugLine(GetWorld(), start, hitResult.Location, FColor::Red, false, 0.5f, 0, 5);
				if (hitResult.Actor.Get())
				{
					UE_LOG(LogTemp, Warning, TEXT("Lazer collided with %s. "), *hitResult.Actor.Get()->GetName());
					AActor* owner = GetOwner();
					AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;
					if (hitResult.Actor.Get() != owner && hitResult.Actor.Get() != ownerByOwner)
					{
						IDamageTaker* damageTakerActor = Cast<IDamageTaker>(hitResult.Actor.Get());
						if (damageTakerActor)
						{
							FDamageData damageData;
							damageData.DamageValue = 1;
							damageData.Instigator = owner;
							damageData.DamageMaker = this;

							damageTakerActor->TakeDamage(damageData);
						}
						else
						{
							hitResult.Actor.Get()->Destroy();
						}
					}

				}
			}
			else
			{
				DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 0.5f, 0, 5);
			}
		}
	}
	Ammo -= 3;
	FireRate = 3;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
}

bool ACannon::IsReadyToFire()
{
	return ReadyToFire;
}

void ACannon::Reload()
{
	if (Ammo > 0)
	{
		ReadyToFire = true;
	}
	else
	{
		ReadyToFire = false;
	}
}

void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();
}