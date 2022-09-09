 //Fill out your copyright notice in the Description page of Project Settings.


#include "DraggableItem.h"
#include <Components/VerticalBox.h>
#include <Blueprint/WidgetBlueprintLibrary.h>
#include <Tankogeddon/TankDragDropOperation.h>


void UDraggableItem::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (TankText)
	{
		TankText->SetText(FText::FromString(TankName));
	}
}

FReply UDraggableItem::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (Cast<UVerticalBox>(GetParent()) && InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}

	return FReply::Handled();
}

void UDraggableItem::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UTankDragDropOperation::StaticClass());
	UTankDragDropOperation* TankOperation = Cast<UTankDragDropOperation>(OutOperation);

	if (TankOperation)
	{
		TankOperation->DefaultDragVisual = this;

		SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.7f));
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		TankOperation->OnDragCancelled.AddDynamic(this, &ThisClass::RestoreVisuals);
	}
	else
	{
		Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	}
}

bool UDraggableItem::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	auto VerticalBox = Cast<UVerticalBox>(GetParent());
	UTankDragDropOperation* TankOperation = Cast<UTankDragDropOperation>(InOperation);

	auto Geometry = this->GetCachedGeometry();

	if (VerticalBox && TankOperation && TankOperation->DefaultDragVisual && this != TankOperation->DefaultDragVisual)
	{
		int32 OverIndex = VerticalBox->GetChildIndex(TankOperation->DefaultDragVisual);

		if (OverIndex >= 0)
		{
			VerticalBox->RemoveChildAt(OverIndex);

			const TArray<UWidget*> Children = VerticalBox->GetAllChildren();
			VerticalBox->ClearChildren();

			for (int32 i = 0; i < Children.Num(); i++)
			{
				VerticalBox->AddChildToVerticalBox(Children[i]); // ->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);

				if (Children[i] == this)
				{
					VerticalBox->AddChildToVerticalBox(TankOperation->DefaultDragVisual); // ->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
				}
			}

			return true;
		}
	}

	return Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
}

bool UDraggableItem::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (InOperation && InOperation->DefaultDragVisual)
	{
		RestoreVisuals(InOperation);
		return true;
	}

	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UDraggableItem::RestoreVisuals(UDragDropOperation* Operation)
{
	if (Cast<UTankDragDropOperation>(Operation) == nullptr)
	{
		return;
	}

	if (UDraggableItem* Item = Cast<UDraggableItem>(Operation->DefaultDragVisual))
	{
		Item->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
		Item->SetVisibility(ESlateVisibility::Visible);
	}
}


