// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "InventoryData.h"
#include "EquipInterface.h"
#include "EquipInventoryComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKOGEDDON_API UEquipInventoryComponent : public UInventoryComponent
{
	GENERATED_BODY()
	
public:

	UEquipInventoryComponent();

	virtual int32 GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& Item) override;

	virtual void SetItem(int32 SlotIndex, const FInventorySlotInfo& Item) override;

	virtual void ClearItem(int32 SlotIndex) override;

	UPROPERTY(EditAnywhere)
	TMap<int32, EEquipSlot> EquipSlots;
};