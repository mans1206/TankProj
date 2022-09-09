// Fill out your copyright notice in the Description page of Project Settings.


#include "HP_Bar_Comp.h"


void UHP_Bar_Comp::SetBar(float Health)
{
	HealthBar->SetPercent(Health);
}

void UHP_Bar_Comp::NativeConstruct()
{
	Super::NativeConstruct();
	HealthBar->SetPercent(1);
}



