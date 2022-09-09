// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "InventoryData.generated.h"

UENUM()
enum class EItemType : uint8
{
	It_Miscelaneous,
	It_Currency,
	It_Equip,
	It_Consumable,
	It_Armor,
	It_Weapon,
	Count UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(EItemType, EItemType::Count);


UENUM()
enum class EItemRarity : uint8
{
	Ir_Common,
	Ir_Rare,
	Ir_Epic,
	Count UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(EItemRarity, EItemRarity::Count);


UENUM()
enum class EEquipSlot : uint8
{
	Es_Turret,
	Es_Cannon,
	Es_Body
};

class UInventoryCellsWidget;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemDrop, UInventoryCellsWidget* , UInventoryCellsWidget* )

USTRUCT(BlueprintType)
struct FInventoryItemInfo : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditDefaultsOnly, Category = "General")
		FName Id;

	UPROPERTY(EditDefaultsOnly, Category = "General")
		FText Name;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
		EItemType Type;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
		EItemRarity Rare;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
		EEquipSlot EquipSlot;

	UPROPERTY(EditDefaultsOnly, Category = "Visual")
		TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, Category = "Visual")
		TSoftObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		int32 Damage;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		int32 Armor;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		int32 Intelligence;
};


USTRUCT(BlueprintType)
struct FInventorySlotInfo //: public FTableRawBase
{
	GENERATED_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		//FName Id = NAME_None;
		FName Id;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int32 Count;
};
