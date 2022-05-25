// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include <string>
#include <sstream>


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

}

float ACannon::GetAmmo()
{
	return Ammo;
}

void ACannon::Fire()
{
	//std::string str = "Fire - projectile, ammount of ammo is: ";
	//char* str2;
	//std::stringstream iostr;
	//iostr << Ammo;
	//iostr >> str2;
	//std::string stri = str + str2;

	

	if (!ReadyToFire)
	{
		return;
	}
	ReadyToFire = false;

	if (Type == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - projectile");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - trace");
	}
	Ammo--;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
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

		if (Type == ECannonType::FireProjectile)
		{
			GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - projectile");
			GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - projectile");
			GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - projectile");
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - trace");
			GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - trace");
			GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - trace");
		}
	}
	Ammo -= 3;
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

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();
}


void ACannon::Tick(float Value) 
{

}