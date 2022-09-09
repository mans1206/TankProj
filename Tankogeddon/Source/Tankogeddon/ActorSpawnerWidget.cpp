// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawnerWidget.h"
#include <Tankogeddon/TankPlayerController.h>
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

void UActorSpawnerWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (DraggedText)
	{
		DraggedText->SetText(FText::FromString(DraggedName));
	}
}

void UActorSpawnerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (auto* MyController = Cast<ATankPlayerController>(PlayerController))
	{
		MyController->OnMouseButtonUp.AddUObject(this, &UActorSpawnerWidget::OnMouseButtonUp);
	}
}

void UActorSpawnerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (SpawnedActor && PlayerController)
	{
		FVector WorldMousePos;
		FVector WorldMouseDir;
		PlayerController->DeprojectMousePositionToWorld(WorldMousePos, WorldMouseDir);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(SpawnedActor);
		Params.AddIgnoredActor(PlayerController->GetPawn());

		FHitResult OutHit;
		constexpr float Dist = 100000.f;
		GetWorld()->LineTraceSingleByChannel(OutHit, WorldMousePos, WorldMousePos + WorldMouseDir * Dist,
			ECollisionChannel::ECC_WorldStatic, Params);

		if (OutHit.bBlockingHit)
		{
			SpawnedActor->SetActorLocation(OutHit.Location);
		}

	}
}


FReply UActorSpawnerWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		SpawnedActor = GetWorld()->SpawnActor<AActor>(SpawnerClass);
	}

	return FReply::Handled();
}

void UActorSpawnerWidget::OnMouseButtonUp()
{
	SpawnedActor = nullptr;
}

