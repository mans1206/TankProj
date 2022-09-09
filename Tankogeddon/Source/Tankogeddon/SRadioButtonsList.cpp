// Fill out your copyright notice in the Description page of Project Settings.

#include "SRadioButtonsList.h"
#include "SlateOptMacros.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Text/STextBlock.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION


void SRadioButtonsList::Construct(const FArguments& InArgs)
{
	OnRadioButtonChanged = InArgs._OnRadioButtonChanged;
	SetRadioButtonStyle(InArgs._Style);

	ChildSlot
	[
		SAssignNew(ButtonsBox, SVerticalBox)
	];

	if (ButtonsBox->NumSlots() != ButtonsCount.Get())
	{
		Create();
	}
	

	//ChildSlot
	//	[
	//		SNew(SVerticalBox)

	//		+ SVerticalBox::Slot()
	//		[
	//			//first button
	//			CreateRadioButton("Option1", 0)
	//		]

	//		+ SVerticalBox::Slot()
	//		[
	//			//second button
	//			CreateRadioButton("Option2", 1)
	//		]

	//		+ SVerticalBox::Slot()
	//		[
	//			//third button
	//			CreateRadioButton("Option3", 2)
	//		]
	//	];

	
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SRadioButtonsList::Create()
{
	ButtonsBox->ClearChildren();

	for (int32 i = 0; i < ButtonsCount.Get(); i++)
	{
		ButtonsBox->AddSlot()
			[
				CreateRadioButton(TEXT("Option " + FString::FromInt(i+1)), i)
			];
	};
	OnRadioButtonChanged.ExecuteIfBound(CurrentChoice);
}

ECheckBoxState SRadioButtonsList::IsRadioButtonChecked(int32 ButtonIndex) const
{
	return (CurrentChoice == ButtonIndex)
		? ECheckBoxState::Checked
		: ECheckBoxState::Unchecked;
}

void SRadioButtonsList::HandleRadioButtonStateChanged(ECheckBoxState NewRadioState, int32 ButtonIndex)
{
	if (NewRadioState == ECheckBoxState::Checked)
	{
		CurrentChoice = ButtonIndex;
		OnRadioButtonChanged.ExecuteIfBound(CurrentChoice);
	}
}

TSharedRef<SWidget> SRadioButtonsList::CreateRadioButton(FString RadioText, int32 ButtonIndex)
{
	return SNew(SCheckBox)
		.IsChecked(MakeAttributeRaw(this, &SRadioButtonsList::IsRadioButtonChecked, ButtonIndex))
		.OnCheckStateChanged(this, &SRadioButtonsList::HandleRadioButtonStateChanged, ButtonIndex)
		.Style(CheckBoxStyle)
		[
			SNew(STextBlock)
			.Text(FText::FromString(RadioText))
			.TextStyle(TextStyle)
		];
}

void SRadioButtonsList::SetRadioButtonStyle(const FRadioButtonsStyle* InStyle)
{
	CheckBoxStyle = &InStyle->CheckBoxStyle;
	TextStyle = &InStyle->TextStyle;
}









