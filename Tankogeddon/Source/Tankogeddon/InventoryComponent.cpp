// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

FInventorySlotInfo* UInventoryComponent::GetItem(int32 SlotIndex)
{
	return Items.Find(SlotIndex);
}

void UInventoryComponent::SetItem(int32 SlotIndex, const FInventorySlotInfo& Item)
{
	ClearItem(SlotIndex);
	Items.Add(SlotIndex, Item);
	//Items.FindOrAdd(SlotIndex) = Item;
}

void UInventoryComponent::ClearItem(int32 SlotIndex)
{
	Items.Remove(SlotIndex);
}

TMap<int32, FInventorySlotInfo>& UInventoryComponent::GetItems()
{
	return Items;
}

int32 UInventoryComponent::GetItemsNum()
{
	return Items.Num();
}

int32 UInventoryComponent::GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& InItem)
{
	FInventorySlotInfo* InfoPtr = Items.Find(SlotIndex);
	if (InfoPtr && InfoPtr->Id != InItem.Id)
	{
		return 0;
	}
	return -1;
}


