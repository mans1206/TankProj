// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include "Animation/WidgetAnimation.h"
#include <Components/NativeWidgetHost.h>
#include <Tankogeddon/RadioButtons.h>
#include <Components/Image.h>
#include "MainMenuWidget.generated.h"



/**
 * 
 */
UCLASS(abstract)

class TANKOGEDDON_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* NewGameBtn;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* ContinueGameBtn;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* OptionsBtn;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* SaveGameBtn;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* ExitGameBtn;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* NextBtn;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		UButton* LastBtn;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
		URadioButtons* MyButtons;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional), Transient)
		UImage* Wolfimage;


	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* NewGameAnimation;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* ContinueGameAnimation;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* OptionsAnimation;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* SaveGameAnimation;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* ArrowsAnimation;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetAnim), Transient)
		UWidgetAnimation* ExitGameAnimation;

	UPROPERTY(EditAnywhere, Category = "Style")
		FName ButtonsStyle;

	UPROPERTY(EditAnywhere, Category = "Style")
		FName RadioButtonsStyle;
	
public:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
	UMainMenuWidget* MainMenu;

protected:
	UFUNCTION()
		void OnNewGameClicked();
	UFUNCTION()
		void OnNewGameHovered();

	UFUNCTION()
		void OnContinueClicked();
	UFUNCTION()
		void OnContinueHovered();

	UFUNCTION()
		void OnOptionsClicked();
	UFUNCTION()
		void OnOptionsHovered();

	UFUNCTION()
		void OnSaveGameClicked();
	UFUNCTION()
		void OnSaveGameHovered();

	UFUNCTION()
		void OnExitGameClicked();
	UFUNCTION()
		void OnExitGameHovered();

	//UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	//	UNativeWidgetHost* RadioButtonsHost;

};
