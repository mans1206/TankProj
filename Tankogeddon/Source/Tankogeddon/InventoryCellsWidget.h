// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryData.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InventoryDragDropOperation.h"
#include "InventoryWidget.h"
#include "InventoryComponent.h"
#include "InventoryCellsWidget.generated.h"

/**
 * 
 */
//DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemDrop, UInventoryCellsWidget*, UInventoryCellsWidget*);



UCLASS()
class TANKOGEDDON_API UInventoryCellsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	bool HasItem() { return bHasItem; }

	bool AddItem(const FInventorySlotInfo& InSlot, const FInventoryItemInfo& Info);

	void Clear();

	const FInventorySlotInfo& GetItem() { return Item; }

	UPROPERTY(EditAnywhere)
	int32 IndexInInventory = -1;

	FOnItemDrop OnItemDrop;

	UPROPERTY()
	class UInventoryWidget* ParentInventoryWidget;

	UInventoryComponent* GetParentInventory() const;

protected:

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

protected:

	UPROPERTY(EditAnywhere)
		bool bCanDrag = true;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		UImage* ItemImage;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
		UTextBlock* CountText;

	bool bHasItem;

	UPROPERTY()
		FInventorySlotInfo Item;
};