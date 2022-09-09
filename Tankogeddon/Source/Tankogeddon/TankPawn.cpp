// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "TankPlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/TargetPoint.h"
#include "Components/ArrowComponent.h"
#include "HP_Bar_Comp.h"
#include "Components/WidgetComponent.h"


/*DECLARE_LOG_CATEGORY_EXTERN(TankLog, All, All);
DEFINE_LOG_CATEGORY(TankLog);*/


// Sets default values
ATankPawn::ATankPawn()
{

	PrimaryActorTick.bCanEverTick = true;


	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank body"));
	BodyMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank turret"));
	TurretMesh->SetupAttachment(BodyMesh);		

	CanonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	CanonSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	HealthComponent->OnDie.AddUObject(this, &ATankPawn::Die);
	HealthComponent->OnDamaged.AddUObject(this, &ATankPawn::DamageTaked);

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit collider"));
	HitCollider->SetupAttachment(BodyMesh);

	DieEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Shoot Effect"));
	DieEffect->SetupAttachment(BodyMesh);

	AudioDieEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Die Effect"));
	AudioDieEffect->SetAutoActivate(false);
	AudioHitEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Hit Effect"));
	AudioHitEffect->SetAutoActivate(false);

	WidgComp = CreateDefaultSubobject<UWidgetComponent>("BarHP");
	WidgComp->SetupAttachment(BodyMesh);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	InventoryManagerComponent = CreateDefaultSubobject<UInventoryManagerComponent>("Inventory Manager");
	EquipmentInventoryComponent = CreateDefaultSubobject<UEquipInventoryComponent>("EquipInventory");


	BodySlot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank slot"));
	BodySlot->SetupAttachment(BodyMesh);

	CanonSlot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Canon slot"));
	CanonSlot->SetupAttachment(TurretMesh);

	TurretSlot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret slot"));
	TurretSlot->SetupAttachment(TurretMesh);
}

void ATankPawn::TakeDamage(FDamageData DamageData)
{
	AudioHitEffect->SetAutoActivate(false);
	AudioHitEffect->Play();

	HealthComponent->TakeDamage(DamageData);

	if (HealthBar)
	{
		HealthBar->SetBar(HealthComponent->GetHealth()/10);
	}
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	TankController = Cast<ATankPlayerController>(GetController());
	SetupCannon(CannonClass);
	auto WidClass = WidgComp->GetWidget();
	HealthBar = Cast<UHP_Bar_Comp>(WidClass);
	//InventoryManagerComponent->Init(InventoryComponent);
	//InventoryManagerComponent->InitEquipment(EquipmentInventoryComponent);
}




void ATankPawn::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("Tank Died"));
	
	AudioDieEffect->SetAutoActivate(false);
	DieEffect->ActivateSystem();
	Destroy();
	AudioDieEffect->Play();
	Cannon->Destroy();
}

void ATankPawn::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Tank %s taked damage:%f Health:%f"), *GetName(),DamageValue, HealthComponent->GetHealth());
}

void ATankPawn::MoveForward(float AxisValue)
{
	TargetForwardAxisValue = AxisValue;
}

void ATankPawn::MoveLeft(float AxisValue)
{
	TargetLeftAxisValue = AxisValue;
}

void ATankPawn::RotateRight(float AxisValue)
{
	TargetRightAxisValue = AxisValue;
}


TSubclassOf<ACannon> OldcanClass;
void ATankPawn::SetupCannon(TSubclassOf<ACannon> cannonClass)
{
	if (cannonClass)
	{
		OldcanClass = CannonClass;
		CannonClass = cannonClass;
	}
	if (Cannon)
	{	
		Cannon->Destroy();
	}
	FActorSpawnParameters params;
	params.Instigator = this;
	params.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, params);
	Cannon->AttachToComponent(CanonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

}

void ATankPawn::ChangeCannon()
{
	if (Cannon)
	{
		SetupCannon(OldcanClass);
	}
}

void ATankPawn::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
}


void ATankPawn::FireSpecial()
{
	if (Cannon)
	{
		Cannon->FireSpecial();
	}
}


void ATankPawn::EquipItem(EEquipSlot Slot, FName ItemId)
{
	if (UStaticMeshComponent* Comp = GetEquipComponent(Slot))
	{
		auto* Info = InventoryManagerComponent->GetItemData(ItemId);
		Comp->SetStaticMesh(Info->Mesh.LoadSynchronous());
		Comp->SetHiddenInGame(false);

		//Damage += Info->Damage;
	}
}

void ATankPawn::UnequipItem(EEquipSlot Slot, FName ItemId)
{
	if (UStaticMeshComponent* Comp = GetEquipComponent(Slot))
	{
		auto* Info = InventoryManagerComponent->GetItemData(ItemId);
		Comp->SetStaticMesh(nullptr);
		Comp->SetHiddenInGame(true);

		//Damage -= Info->Damage;
	}
}

UStaticMeshComponent* ATankPawn::GetEquipComponent(EEquipSlot EquipSlot)
{
	FName Tag;
	
	switch (EquipSlot)
	{
	case EEquipSlot::Es_Body: Tag = "Body"; break;
	case EEquipSlot::Es_Turret: Tag = "Turret"; break;
	case EEquipSlot::Es_Cannon: Tag = "Cannon"; break;
	default: return nullptr;
	}

	TArray<UActorComponent*> Found = GetComponentsByTag(UStaticMeshComponent::StaticClass(), Tag);

	return Found.Num() > 0 ? Cast<UStaticMeshComponent>(Found[0]) : nullptr;
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Tank Movement
	FVector currentLocation = GetActorLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector leftVector = GetActorRightVector();
	FVector movePosition;
	movePosition = currentLocation + forwardVector * MovementSpeed * TargetForwardAxisValue * DeltaTime + 
	(leftVector * TargetLeftAxisValue * (MovementSpeed/100));
	SetActorLocation(movePosition, true);

	//Tank Rotation
	CurrentRightAxisValue = FMath::Lerp(CurrentRightAxisValue, TargetRightAxisValue, InterpolationKey);
	//UE_LOG(LogTemp, Warning, TEXT("CurrentRightAxisValue = %f TargetRightAxisValue = % f"), CurrentRightAxisValue, TargetRightAxisValue);
	float yawRotation = RotationSpeed * CurrentRightAxisValue * DeltaTime;
	FRotator currentRotation = GetActorRotation();
	yawRotation = currentRotation.Yaw + yawRotation;
	FRotator newRotation = FRotator(0, yawRotation, 0);
	SetActorRotation(newRotation);

	//turret Rotation

	if (TankController)
	{
		FVector mousePos = TankController->GetmousePos();
		FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mousePos);
		FRotator currRotation = TurretMesh->GetComponentRotation();
		targetRotation.Pitch = currRotation.Pitch;
		targetRotation.Roll = currRotation.Roll;
		TurretMesh->SetWorldRotation(FMath::Lerp(currRotation, targetRotation, TurretRotationInterpolationKey));
	}
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector ATankPawn::GetTurretForwardVector()
{
	return TurretMesh->GetForwardVector();
}

void ATankPawn::RotateTurretTo(FVector TargetPosition)
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPosition);
	FRotator currRotation = TurretMesh->GetComponentRotation();
	targetRotation.Pitch = currRotation.Pitch;
	targetRotation.Roll = currRotation.Roll;
	TurretMesh->SetWorldRotation(FMath::Lerp(currRotation, targetRotation, TurretRotationInterpolationKey));
}

FVector ATankPawn::GetEyesPosition()
{
	return CanonSetupPoint->GetComponentLocation();
}

TArray <FVector> ATankPawn::GetPatrollingPoints()
{
	TArray<FVector> points;
	for (ATargetPoint * point : PatrollingPoints)
	{
		points.Add(point->GetActorLocation());
	}
	return points;
}

void ATankPawn::SetPatrollingPoints(TArray<ATargetPoint*> NewPatrollingPoints)
{
	PatrollingPoints = NewPatrollingPoints;
}