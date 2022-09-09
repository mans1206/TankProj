// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipInventoryComponent.h"

UEquipInventoryComponent::UEquipInventoryComponent()
{
	EquipSlots.Add(0, EEquipSlot::Es_Turret);
	EquipSlots.Add(1, EEquipSlot::Es_Cannon);
	EquipSlots.Add(2, EEquipSlot::Es_Body);
}

int32 UEquipInventoryComponent::GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& Item)
{
	EEquipSlot* EquipSlotPtr = EquipSlots.Find(SlotIndex);
	if (Item.Type == EItemType::It_Equip && EquipSlotPtr && *EquipSlotPtr == Item.EquipSlot)
	{
		return 1;
	}
	return 0;
}

void UEquipInventoryComponent::SetItem(int32 SlotIndex, const FInventorySlotInfo& Item)
{
	auto* InventoryOwner = GetOwner();
	if (!InventoryOwner->GetClass()->ImplementsInterface(UEquipInterface::StaticClass()))
	{
		Super::SetItem(SlotIndex, Item);
		return;
	}

	if (IEquipInterface* EquipInterface = Cast<IEquipInterface>(InventoryOwner))
	{
		EEquipSlot EquipSlot = EquipSlots.FindChecked(SlotIndex);
		if (auto* ItemInfo = GetItem(SlotIndex))
		{
			EquipInterface->UnequipItem(EquipSlot, ItemInfo->Id);
		}

		Super::SetItem(SlotIndex, Item);

		EquipInterface->EquipItem(EquipSlot, Item.Id);
	}

}

void UEquipInventoryComponent::ClearItem(int32 SlotIndex)
{
	auto* InventoryOwner = GetOwner();
	if (!InventoryOwner->GetClass()->ImplementsInterface(UEquipInterface::StaticClass()))
	{
		Super::ClearItem(SlotIndex);
		return;
	}

	if (IEquipInterface* EquipInterface = Cast<IEquipInterface>(InventoryOwner))
	{
		EEquipSlot EquipSlot = EquipSlots.FindChecked(SlotIndex);
		if (auto* ItemInfo = GetItem(SlotIndex))
		{
			EquipInterface->UnequipItem(EquipSlot, ItemInfo->Id);
		}

		Super::ClearItem(SlotIndex);
	}
}