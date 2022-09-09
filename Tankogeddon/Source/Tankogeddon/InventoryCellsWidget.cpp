// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryCellsWidget.h"
#include <Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h>


bool UInventoryCellsWidget::AddItem(const FInventorySlotInfo& InSlot, const FInventoryItemInfo& Info)
{
	if (bHasItem)
	{
		return false;
	}

	if (ItemImage)
	{
		ItemImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		ItemImage->SetBrushFromTexture(Info.Icon.LoadSynchronous());
	}

	if (CountText)
	{
		CountText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		CountText->SetText(FText::FromString(FString::FromInt(InSlot.Count)));
	}

	bHasItem = true;
	Item = InSlot;

	return true;
}

void UInventoryCellsWidget::Clear()
{
	if (!bHasItem)
	{
		return;
	}

	if (ItemImage)
	{
		ItemImage->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (CountText)
	{
		CountText->SetVisibility(ESlateVisibility::Collapsed);
	}

	bHasItem = false;
	Item = FInventorySlotInfo();
}

UInventoryComponent* UInventoryCellsWidget::GetParentInventory() const
{
	return ParentInventoryWidget ? ParentInventoryWidget->ParentInventory : nullptr;
}

FReply UInventoryCellsWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bCanDrag && bHasItem && InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
	return FReply::Handled();
}

void UInventoryCellsWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UInventoryDragDropOperation::StaticClass());
	if (OutOperation)
	{
		UInventoryDragDropOperation* InventoryDragDropOperation = Cast<UInventoryDragDropOperation>(OutOperation);

		InventoryDragDropOperation->SourceCell = this;
		InventoryDragDropOperation->DefaultDragVisual = this;

	}
	else
	{
		Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	}
}

bool UInventoryCellsWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UInventoryDragDropOperation* InventoryDragDropOperation = Cast<UInventoryDragDropOperation>(InOperation);

	if (InventoryDragDropOperation && InventoryDragDropOperation->SourceCell != this)
	{
		if (OnItemDrop.IsBound())
		{
			OnItemDrop.Broadcast(InventoryDragDropOperation->SourceCell, this);
		}
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}