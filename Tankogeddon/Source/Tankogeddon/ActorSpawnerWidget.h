// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "GameFramework/Actor.h"
#include "Components/Button.h"
#include "ActorSpawnerWidget.generated.h"


class UTextBlock;

/**
 * 
 */
UCLASS()
class TANKOGEDDON_API UActorSpawnerWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	UPROPERTY(BlueprintCallable, Category = "Button|Event")
		FOnButtonHoverEvent OnHovered;

protected:

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> SpawnerClass;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UTextBlock* DraggedText;

	UPROPERTY(EditAnywhere)
		FString DraggedName;

	UPROPERTY()
		AActor* SpawnedActor = nullptr;

	UPROPERTY()
		APlayerController* PlayerController;

	void OnMouseButtonUp();
	


};
