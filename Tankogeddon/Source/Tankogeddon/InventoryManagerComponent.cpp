#include "InventoryManagerComponent.h"

UInventoryManagerComponent::UInventoryManagerComponent()
{

}

void UInventoryManagerComponent::Init(UInventoryComponent* InInventoryComponent)
{
	LocalInventoryComponent = InInventoryComponent;

	if (LocalInventoryComponent && InventoryItemsData /*&& InventoryWidetClass*/)
	{
		//ensure(InventoryWidetClass);

		InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidetClass);
		InventoryWidget->AddToViewport();
		InventoryWidget->ParentInventory = InInventoryComponent;

		InventoryWidget->Init(FMath::Max(LocalInventoryComponent->GetItemsNum(), MinInventorySize));
		InventoryWidget->OnItemDrop.AddUObject(this, &UInventoryManagerComponent::OnItemDropFunc);
		
		
		//[SlotIndex, SlotInfo]

		for (auto& Item : LocalInventoryComponent->GetItems())
		{
			FInventoryItemInfo* ItemData = GetItemData(Item.Value.Id);

			if (ItemData)
			{
				//FString ItemDataStr = ItemData->Name.ToString() + ": " + FString::FromInt(Item.Value.Count);
				ItemData->Icon.LoadSynchronous();
				InventoryWidget->AddItem(Item.Value, *ItemData, Item.Key);
			}
		}
	}
}

void UInventoryManagerComponent::OnItemDropFunc(UInventoryCellsWidget* From, UInventoryCellsWidget* To)
{
	if (From == nullptr || To == nullptr)
	{
		return;
	}
	
	auto* FromInventory = From->GetParentInventory();
	auto* ToInventory = To->GetParentInventory();

	if (FromInventory == nullptr || ToInventory == nullptr)
	{
		return;
	}
	
	FInventorySlotInfo FromItem = From->GetItem();
	if (FromItem.Count == 0)
	{
		return;
	}

	const FInventorySlotInfo ToItem = To->GetItem();
	const FInventoryItemInfo* FromInfo = GetItemData(FromItem.Id);

	const int32 ToItemAmount = ToInventory->GetMaxItemAmount(To->IndexInInventory, *FromInfo);
	if (ToItemAmount == 0)
	{
		return;
	}


	FInventorySlotInfo NewFromItem = ToItem;
	FInventorySlotInfo NewToItem = FromItem;

	if (ToItemAmount > 0)
	{
		NewToItem.Count = FMath::Max(ToItemAmount, FromItem.Count);
		if (FromItem.Count <= NewToItem.Count)
		{
			NewFromItem.Id = NewToItem.Id;
			NewFromItem.Count = FromItem.Count - NewToItem.Count;
		}
	}

	const FInventoryItemInfo* NewFromInfo = NewFromItem.Count > 0 ? GetItemData(NewFromItem.Id) : nullptr;
	const FInventoryItemInfo* NewToInfo = GetItemData(NewToItem.Id);

	From->Clear();
	if (NewFromInfo)
	{
		From->AddItem(NewFromItem, *NewFromInfo);
	}

	To->Clear();
	To->AddItem(NewToItem, *NewToInfo);

	FromInventory->SetItem(From->IndexInInventory, NewFromItem);
	ToInventory->SetItem(To->IndexInInventory, NewToItem);

	/*if (!ToItem.Id.IsNone())
	{
		From->AddItem(ToItem, *GetItemData(ToItem.Id));
	}*/
}

void UInventoryManagerComponent::InitEquipment(UInventoryComponent* InInventoryComponent)
{
	//ensure(EquipInventoryWidgetClass);
	if (InInventoryComponent && EquipInventoryWidgetClass)
	{
		EquipInventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), EquipInventoryWidgetClass);
		EquipInventoryWidget->ParentInventory = InInventoryComponent;
		EquipInventoryWidget->OnItemDrop.AddUObject(this, &UInventoryManagerComponent::OnItemDropFunc);
		EquipInventoryWidget->AddToViewport();
	}
}

FInventoryItemInfo* UInventoryManagerComponent::GetItemData(const FName& InID)
{
	return InventoryItemsData ? InventoryItemsData->FindRow<FInventoryItemInfo>(InID, "") : nullptr;
}

FInventoryItemInfo* UInventoryManagerComponent::GetChestItemData(const FName& InID)
{
	return ChestItemsData ? ChestItemsData->FindRow<FInventoryItemInfo>(InID, "") : nullptr;
}


void UInventoryManagerComponent::InitChest(UInventoryComponent* InInventoryComponent)
{

	if (InInventoryComponent && ChestItemsData)
	{
		ChestInventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), ChestInventoryWidgetClass);
		ChestInventoryWidget->AddToViewport();
		ChestInventoryWidget->ParentInventory = InInventoryComponent;
		ChestInventoryWidget->Init(FMath::Max(InInventoryComponent->GetItemsNum(), MinInventorySize));
		ChestInventoryWidget->OnItemDrop.AddUObject(this, &UInventoryManagerComponent::OnItemDropFunc);
		
		for (auto& Item : InInventoryComponent->GetItems())
		{
			FInventoryItemInfo* ChestItemData = GetChestItemData(Item.Value.Id);

			if (ChestItemData)
			{
				//FString ItemDataStr = ItemData->Name.ToString() + ": " + FString::FromInt(Item.Value.Count);
				ChestItemData->Icon.LoadSynchronous();
				ChestInventoryWidget->AddItem(Item.Value, *ChestItemData, Item.Key);
			}
			
		}
	}
}

