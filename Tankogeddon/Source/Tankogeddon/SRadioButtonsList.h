// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "RadioButtonsWidgetStyle.h"


//UENUM(BlueprintType)
//enum class ERadioChoice : uint8
//{
//	Radio0,
//	Radio1,
//	Radio2,
//};

DECLARE_DELEGATE_OneParam(FOnRadioButtonChanged, int32 /*NewRadioChoice*/);


class TANKOGEDDON_API SRadioButtonsList : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SRadioButtonsList)
	{
	}

		SLATE_EVENT(FOnRadioButtonChanged, OnRadioButtonChanged)

		SLATE_STYLE_ARGUMENT(FRadioButtonsStyle, Style)


	SLATE_END_ARGS()


	void SetRadioButtonStyle(const FRadioButtonsStyle* InStyle);

	void Construct(const FArguments& InArgs);

	TAttribute<int32> ButtonsCount;

	int32 CurrentChoice;

	void Create();

	FOnRadioButtonChanged OnRadioButtonChanged;

protected:

	TSharedRef<SWidget> CreateRadioButton(FString RadioText, int32 RadioButtonIndex);
	
	ECheckBoxState IsRadioButtonChecked(int32 ButtonIndex) const;

	void HandleRadioButtonStateChanged(ECheckBoxState NewRadioState, int32 ButtonIndex);

	TSharedPtr<SVerticalBox> ButtonsBox;

	const FCheckBoxStyle* CheckBoxStyle = nullptr;
	const FTextBlockStyle* TextStyle = nullptr;
};