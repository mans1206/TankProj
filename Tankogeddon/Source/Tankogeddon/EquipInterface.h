// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CoreMinimal.h"
#include "InventoryData.h"
#include "UObject/Interface.h"
#include "EquipInterface.generated.h"


UINTERFACE(MinimalAPI, Blueprintable)
class UEquipInterface : public UInterface
{
	GENERATED_BODY()
};


class TANKOGEDDON_API IEquipInterface
{
	GENERATED_BODY()

public:
	virtual void EquipItem(EEquipSlot Slot, FName ItemID) {}
	virtual void UnequipItem(EEquipSlot Slot, FName ItemID) {}
};
