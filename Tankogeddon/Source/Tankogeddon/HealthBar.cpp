// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBar.h"
#include <Tankogeddon/HealthComponent.h>

float UHealthBar::GetHealthPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return 0.0f;

	const auto Component = Player->GetComponentByClass(UHealthComponent::StaticClass());
	const auto HealthComp = Cast<UHealthComponent>(Component);
	if (!HealthComp) return 0.0f;

	return HealthComp->GetHealthPercent();
}
