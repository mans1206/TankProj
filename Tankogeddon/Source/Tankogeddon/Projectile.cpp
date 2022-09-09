// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include <Tankogeddon/DamageTaker.h>
#include <Runtime/Engine/Public/DrawDebugHelpers.h>


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* sceeneCpm = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceeneCpm;	

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMeshOverlapBegin);
	Mesh->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
}

void AProjectile::Start()
{
	GetWorld()->GetTimerManager().SetTimer(MovementTimerHandle, this,&AProjectile::Move, MoveRate, true, MoveRate);
}

void AProjectile::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor*OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile %s collided with %s. "), *GetName(), *OtherActor->GetName());
	
	if (IsExplode())
	{
		Explode();
	}
	AActor* owner = GetOwner();
	AActor* ownerByOwner = owner != nullptr ? owner->GetOwner() : nullptr;
	if (OtherActor != owner && OtherActor != ownerByOwner)
	{
		IDamageTaker* damageTakerActor = Cast<IDamageTaker>(OtherActor);
		if (damageTakerActor)
		{
			FDamageData damageData;
			damageData.DamageValue = Damage;
			damageData.Instigator = owner;
			damageData.DamageMaker = this;
			damageTakerActor->TakeDamage(damageData);
		}
		else
		{
			UPrimitiveComponent*  mesh = Cast<UPrimitiveComponent>(OtherActor->GetRootComponent());
			if (mesh)
			{
				if (mesh->IsSimulatingPhysics())
				{
					FVector forceVector = OtherActor->GetActorLocation() - GetActorLocation();
					forceVector.Normalize();

					//mesh->AddForce(forceVector * PushForce * mesh->GetMass(), NAME_None, true);
					mesh->AddImpulse(forceVector * PushForce, NAME_None,true);
				}
				else
				{
					OtherActor->Destroy();
				}
			}
		}

		Destroy();
	}

}

void AProjectile::Move()
{
	FVector nextPosition = GetActorLocation() + GetActorForwardVector() * MoveSpeed	* MoveRate;
	SetActorLocation(nextPosition);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AProjectile::IsExplode()
{
	return isExplodeEnabled;
}

void AProjectile::Explode()
{
	FVector startPos = GetActorLocation();
	FVector endPos = startPos + FVector(0.1f);

	FCollisionShape Shape = FCollisionShape::MakeSphere(ExplodeRadius);

	FCollisionQueryParams params = FCollisionQueryParams::DefaultQueryParam;
	params.AddIgnoredActor(this);
	params.bTraceComplex = true;
	params.TraceTag = "Explode Trace";
	TArray<FHitResult> AttackHit;

	FQuat Rotation = FQuat::Identity;

	bool sweepResult = GetWorld()->SweepMultiByChannel
	(
		AttackHit,
		startPos,
		endPos,
		Rotation,
		ECollisionChannel::ECC_Visibility,
		Shape,
		params
	);

	GetWorld()->DebugDrawTraceTag = "Explode Trace";
	//DrawDebugSphere(GetWorld(), startPos, ExplodeRadius, 8, FColor::Purple, true, 1, 0);


	if (sweepResult)
	{
		for (FHitResult hitResult : AttackHit)
		{
			AActor* otherActor = hitResult.GetActor();
			if (!otherActor)
				continue;

			IDamageTaker* damageTakerActor = Cast<IDamageTaker>(otherActor);
			if (damageTakerActor)
			{
				FDamageData damageData;
				damageData.DamageValue = Damage;
				damageData.Instigator = GetOwner();
				damageData.DamageMaker = this;
				damageTakerActor->TakeDamage(damageData);
			}
			else
			{
				UPrimitiveComponent* mesh = Cast<UPrimitiveComponent>(otherActor->GetRootComponent());
				if (mesh)
				{
					if (mesh->IsSimulatingPhysics())
					{
						FVector forceVector = otherActor->GetActorLocation() - GetActorLocation();
						forceVector.Normalize();
						mesh->AddImpulse(forceVector * PushForce, NAME_None, true);
					}
					else
					{
						otherActor->Destroy();
					}
				}
			}
		}
	}
}

//void proverka(AActor * otherActor)
//{
//	IDamageTaker* damageTakerActor = Cast<IDamageTaker>(otherActor);
//	
//	if (damageTakerActor)
//	{
//		FDamageData damageData;
//		damageData.DamageValue = 1;
//		damageData.Instigator = otherActor->GetOwner();
//		damageData.DamageMaker = otherActor;
//		damageTakerActor->TakeDamage(damageData);
//	}
//	else 
//	{
//		UPrimitiveComponent* mesh = Cast<UPrimitiveComponent>(otherActor->GetRootComponent());
//		if (mesh->IsSimulatingPhysics())
//		{
//			FVector forceVector = otherActor->GetActorLocation() - AProjectile::GetActorLocation();
//			forceVector.Normalize();
//			mesh->AddImpulse(forceVector * 100, NAME_None, true);
//		}
//		else
//		{
//			otherActor->Destroy();
//		}
//	}
//}