// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretSpawnerPopup.h"

void UTurretSpawnerPopup::NativeConstruct()
{
	Super::NativeConstruct();
	if (Turret1)
	{
		Turret1->OnHovered.AddDynamic(this, &UTurretSpawnerPopup::OnTurretHovered);
	}
	if (Turret2)
	{
		Turret2->OnHovered.AddDynamic(this, &UTurretSpawnerPopup::OnTurretHovered);
	}
	if (Turret3)
	{
		Turret3->OnHovered.AddDynamic(this, &UTurretSpawnerPopup::OnTurretHovered);
	}

}

void UTurretSpawnerPopup::OnTurretHovered()
{
	MyAnchor->MenuClass;
}
