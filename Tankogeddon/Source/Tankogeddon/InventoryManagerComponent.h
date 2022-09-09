
#pragma once

#include "CoreMinimal.h"
#include "InventoryData.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.h"
#include "InventoryWidget.h"
#include <Tankogeddon/InventoryCellsWidget.h>
#include "InventoryManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKOGEDDON_API UInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UInventoryManagerComponent();

	void Init(UInventoryComponent* InInventoryComponent);

	FInventoryItemInfo* GetItemData(const FName& InID);

	FInventoryItemInfo* GetChestItemData(const FName& InID);

	UPROPERTY()
		UInventoryComponent* LocalInventoryComponent;

	UPROPERTY(EditAnywhere)
		UDataTable* InventoryItemsData;

	UPROPERTY(EditAnywhere)
		UDataTable* ChestItemsData;

	UPROPERTY()
		UInventoryWidget* InventoryWidget;

	UPROPERTY(EditAnywhere)
		int32 MinInventorySize;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UInventoryWidget> InventoryWidetClass;

	void OnItemDropFunc(UInventoryCellsWidget* From, UInventoryCellsWidget* To);

	void InitEquipment(UInventoryComponent* InInventoryComponent);

	void InitChest(UInventoryComponent* InInventoryComponent);

protected:

	UPROPERTY()
		UInventoryWidget* ChestInventoryWidget;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UInventoryWidget> ChestInventoryWidgetClass;

	UPROPERTY()
		UInventoryWidget* EquipInventoryWidget;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UInventoryWidget> EquipInventoryWidgetClass;


};


