// Fill out your copyright notice in the Description page of Project Settings.


#include "RadioButtons.h"
#include "SRadioButtonsList.h"

void URadioButtons::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyRadioButtons.Reset();
}


void URadioButtons::HandleOnRadioChoiceChanged(int32 NewRadioChoice)
{
	if (OnRadioChoiceChanged.IsBound())
	{
		OnRadioChoiceChanged.Broadcast(NewRadioChoice);
	}
}

TSharedRef<SWidget> URadioButtons::RebuildWidget()
{
	MyRadioButtons = SNew(SRadioButtonsList)
		.Style(&WidgetStyle)
		.OnRadioButtonChanged_UObject(this, &ThisClass::HandleOnRadioChoiceChanged);
	MyRadioButtons->ButtonsCount = ButtonsCount;
	MyRadioButtons->CurrentChoice = ButtonChosen;
	MyRadioButtons->Create();

	return MyRadioButtons.ToSharedRef();
}

