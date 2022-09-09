// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "TankPawn.h"
#include "Misc/EnumRange.h"


void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (Armor)
	{
		Armor->OnClicked.AddDynamic(this, &UInventoryWidget::OnArmorClicked);
	}

	if (Weapon)
	{
		Weapon->OnClicked.AddDynamic(this, &UInventoryWidget::OnWeaponClicked);
	}

	if (All)
	{
		All->OnClicked.AddDynamic(this, &UInventoryWidget::OnAllClicked);
	}

	for (UInventoryCellsWidget* CellWidget : CellWidgets)
	{
		InitCellWidget(CellWidget);
	}
}


void UInventoryWidget::OnArmorClicked()
{
	auto TankPawn = Cast<ATankPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto InvManager = TankPawn->GetInventoryManager();
	auto InvComp = TankPawn->GetInventoryComponent();

	TMap<uint8, FInventorySlotInfo> Items;
	uint8 place = 0;

	for (EItemType type : TEnumRange<EItemType>())
	{
		for (auto& Item : InvComp->GetItems())
		{
			FInventorySlotInfo* SlotData = InvComp->GetItem(Item.Key);
			FInventoryItemInfo* ItemData = InvManager->GetItemData(Item.Value.Id);
			if (ItemData && ItemData->Type == EItemType::It_Armor)
			{
				Items.FindOrAdd(place, *SlotData);
				place++;
			}
		}
	}

	Init(10);

	for (const auto& Item : Items)
	{
		FInventoryItemInfo* ItemData = InvManager->GetItemData(Item.Value.Id);
		if (ItemData)
		{
			ItemData->Icon.LoadSynchronous();
			AddItem(Item.Value, *ItemData, Item.Key);
		}
		else
		{
			UE_LOG(LogActor, Warning, TEXT("No Item Data!"));
		}
	}
}

void UInventoryWidget::OnWeaponClicked()
{
	auto TankPawn = Cast<ATankPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto InvManager = TankPawn->GetInventoryManager();
	auto InvComp = TankPawn->GetInventoryComponent();

	TMap<uint8, FInventorySlotInfo> Items;
	uint8 place = 0;

	for (EItemType type : TEnumRange<EItemType>())
	{
		for (auto& Item : InvComp->GetItems())
		{
			FInventorySlotInfo* SlotData = InvComp->GetItem(Item.Key);
			FInventoryItemInfo* ItemData = InvManager->GetItemData(Item.Value.Id);
			if (ItemData && ItemData->Type == EItemType::It_Weapon)
			{
				Items.FindOrAdd(place, *SlotData);
				place++;
			}
		}
	}

	Init(10);

	for (const auto& Item : Items)
	{
		FInventoryItemInfo* ItemData = InvManager->GetItemData(Item.Value.Id);
		if (ItemData)
		{
			ItemData->Icon.LoadSynchronous();
			AddItem(Item.Value, *ItemData, Item.Key);
		}
		else
		{
			UE_LOG(LogActor, Warning, TEXT("No Item Data!"));
		}
	}
}

void UInventoryWidget::OnAllClicked()
{
	auto TankPawn = Cast<ATankPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
	TankPawn->GetInventoryManager()->Init(TankPawn->GetInventoryComponent());
}


void UInventoryWidget::Init(int32 ItemsCount)
{
	if (ItemCellsGrid)
	{
		ItemCellsGrid->ClearChildren();
		for (int32 i = 0; i < ItemsCount; i++)
		{
			if (auto* Cell = CreateCell())
			{
				Cell->IndexInInventory = i;
				ItemCellsGrid->AddChildToUniformGrid(Cell, i / ItemInRow, i % ItemInRow);
			}
		}
	}
}

bool UInventoryWidget::AddItem(const FInventorySlotInfo& InSlot, const FInventoryItemInfo& Info, int32 SlotIndex)
{
	if (Info.Type == EItemType::It_Currency)
	{
		if (GoldCell)
		{
			return GoldCell->AddItem(InSlot, Info);
		}
	}

	if (ItemCellsGrid)
	{
		UInventoryCellsWidget* Found = nullptr;
		UInventoryCellsWidget** FoundPtr = CellWidgets.FindByPredicate([&SlotIndex](UInventoryCellsWidget* Cell)
			{
				return Cell && Cell->IndexInInventory == SlotIndex;
			});

		if (FoundPtr)
		{
			Found = *FoundPtr;
		}
		else
		{
			for (const auto& Cell : CellWidgets)
			{
				if (!Cell->HasItem())
				{
					Found = Cell;
					break;
				}
			}
		}

		if (Found)
		{
			return Found->AddItem(InSlot, Info);
		}
	}
	return false;
}

UInventoryCellsWidget* UInventoryWidget::CreateCell()
{
	if (CellWidgetClass)
	{
		auto* Cell = CreateWidget<UInventoryCellsWidget>(this, CellWidgetClass);
		CellWidgets.Add(Cell);

		InitCellWidget(Cell);

		return Cell;
	}
	return nullptr;
}

void UInventoryWidget::InitCellWidget(UInventoryCellsWidget* Widget)
{
	if (Widget)
	{
		Widget->OnItemDrop.AddUObject(this, &UInventoryWidget::OnItemDropFunc);
		Widget->ParentInventoryWidget = this;
	}
}


void UInventoryWidget::OnItemDropFunc(UInventoryCellsWidget* From, UInventoryCellsWidget* To)
{
	if (OnItemDrop.IsBound())
	{
		OnItemDrop.Broadcast(From, To);
	}
	
}
