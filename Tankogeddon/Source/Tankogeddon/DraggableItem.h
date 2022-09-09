// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "DraggableItem.generated.h"


UCLASS()
class TANKOGEDDON_API UDraggableItem : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FString TankName;

	void NativePreConstruct() override;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TankText;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UFUNCTION()
	void RestoreVisuals(UDragDropOperation* Operation);
};
