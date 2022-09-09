// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Tankogeddon/ActorSpawnerWidget.h>
#include <Components/MenuAnchor.h>
#include "TurretSpawnerPopup.generated.h"


/**
 * 
 */
UCLASS()
class TANKOGEDDON_API UTurretSpawnerPopup : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UActorSpawnerWidget* Turret1;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UActorSpawnerWidget* Turret2;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UActorSpawnerWidget* Turret3;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UMenuAnchor* MyAnchor;

public:
	virtual void NativeConstruct() override;
	UTurretSpawnerPopup* MainPopup;

protected:
	UFUNCTION(BlueprintCallable)
		void OnTurretHovered();
};
