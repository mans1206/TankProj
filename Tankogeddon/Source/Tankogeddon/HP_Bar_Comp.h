// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/ProgressBar.h>
#include "HP_Bar_Comp.generated.h"



/**
 * 
 */
UCLASS()
class TANKOGEDDON_API UHP_Bar_Comp : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
		UProgressBar* HealthBar;

public:

	UFUNCTION(BlueprintCallable)
	void SetBar(float Health);

	virtual void NativeConstruct() override;
};
