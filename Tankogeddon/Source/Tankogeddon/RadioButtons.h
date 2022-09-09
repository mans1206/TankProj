// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include <Tankogeddon/SRadioButtonsList.h>
#include "RadioButtonsWidgetStyle.h"
#include "RadioButtons.generated.h"

class SRadioButtonsList;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRadioChoiceChangedEvent, int32, NewSelectedButton);

/**
 * 
 */
UCLASS()
class TANKOGEDDON_API URadioButtons : public UWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintAssignable, Category = "RadioButtons | Event")
	FOnRadioChoiceChangedEvent OnRadioChoiceChanged;

	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (DisplayName = "Style"))
	FRadioButtonsStyle WidgetStyle;


	virtual void ReleaseSlateResources(bool bReleaseChildren) override;


protected:

	virtual TSharedRef<SWidget> RebuildWidget() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ButtonsCount = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 ButtonChosen = 0;
private:

	TSharedPtr<SRadioButtonsList> MyRadioButtons;

	void HandleOnRadioChoiceChanged(int32 NewRadioChoice);
};
