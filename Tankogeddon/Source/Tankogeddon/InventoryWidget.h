// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryData.h"
#include "Blueprint/UserWidget.h"
#include <Tankogeddon/InventoryCellsWidget.h>
#include <Components/UniformGridPanel.h>
#include <Components/Button.h>
#include "InventoryWidget.generated.h"
/**
 * 
 */
UCLASS()
class TANKOGEDDON_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	virtual void NativeConstruct() override;

	void Init(int32 ItemsCount);

	bool AddItem(const FInventorySlotInfo& InSlot, const FInventoryItemInfo& Info, int32 SlotIndex);

	FOnItemDrop OnItemDrop;

	void InitCellWidget(UInventoryCellsWidget* Widget);

	UPROPERTY()
	class UInventoryComponent* ParentInventory;

protected:

	UPROPERTY(EditDefaultsOnly)
		int32 ItemInRow = 5;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UInventoryCellsWidget> CellWidgetClass;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidgetOptional))
		UUniformGridPanel* ItemCellsGrid;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidgetOptional))
		UButton* Weapon;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidgetOptional))
		UButton* Armor;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidgetoptional))
		UButton* All;

	UFUNCTION()
		void OnArmorClicked();
	UFUNCTION()
		void OnWeaponClicked();
	UFUNCTION()
		void OnAllClicked();


	UPROPERTY(BlueprintReadOnly, Meta = (BindWidgetOptional))
		UInventoryCellsWidget* GoldCell;

	UPROPERTY(BlueprintReadWrite)
		TArray<UInventoryCellsWidget*> CellWidgets;

	UInventoryCellsWidget* CreateCell();

	void OnItemDropFunc(UInventoryCellsWidget* From, UInventoryCellsWidget* To);
};