// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryData.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=("Inventory"), meta=(BlueprintSpawnableComponent) )
class TANKOGEDDON_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	FInventorySlotInfo* GetItem(int32 SlotIndex);

	virtual void SetItem(int32 SlotIndex, const FInventorySlotInfo& Item);

	virtual void ClearItem(int32 SlotIndex);

	TMap<int32, FInventorySlotInfo>& GetItems();

	int32 GetItemsNum();

	virtual int32 GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& InItem);

protected:
	
	/* Cell index -> item */
	UPROPERTY(EditAnywhere)
		TMap<int32, FInventorySlotInfo> Items;

		
};
