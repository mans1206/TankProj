// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h>
#include "SRadioButtonsList.h"
#include <Tankogeddon/MyCoreStyle.h>
#include <Runtime/UMG/Public/Components/ButtonSlot.h>
#include <Tankogeddon/MainMenuWidgetStyle.h>


void UMainMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	//Делали во время урока

	/*if (NewGameBtn)
	{
		NewGameBtn->SetBackgroundColor(MyCoreStyle::Get().GetColor("Red"));
	}

	if (MyButtons)
	{
		MyButtons->WidgetStyle = MyCoreStyle::Get().GetWidgetStyle<FRadioButtonsStyle>(FName("RadioButtonsStyle"));
	}
	if (Wolfimage)
	{
		Wolfimage->SetBrush(*MyCoreStyle::Get().GetBrush("wolf"));
		if (auto* Button = Cast<UButtonSlot>(Wolfimage->Slot))
		{
			Button->SetPadding(MyCoreStyle::Get().GetMargin("DefaultPadding"));
		}
	}*/

	//==========================================================================================================================
	//Домашняя работа
	//==========================================================================================================================

	if (NewGameBtn)
	{
		NewGameBtn->WidgetStyle = MyCoreStyle::Get().GetWidgetStyle<FButtonStyle>(ButtonsStyle);
	}
	if (ContinueGameBtn)
	{
		ContinueGameBtn->WidgetStyle = MyCoreStyle::Get().GetWidgetStyle<FButtonStyle>(ButtonsStyle);
	}
	if (OptionsBtn)
	{
		OptionsBtn->WidgetStyle = MyCoreStyle::Get().GetWidgetStyle<FButtonStyle>(ButtonsStyle);
	}
	if (NextBtn)
	{
		NextBtn->WidgetStyle = MyCoreStyle::Get().GetWidgetStyle<FButtonStyle>(ButtonsStyle);
	}
	if (LastBtn)
	{
		LastBtn->WidgetStyle = MyCoreStyle::Get().GetWidgetStyle<FButtonStyle>(ButtonsStyle);
	}
	if (SaveGameBtn)
	{
		SaveGameBtn->WidgetStyle = MyCoreStyle::Get().GetWidgetStyle<FButtonStyle>(ButtonsStyle);
	}
	if (ExitGameBtn)
	{
		ExitGameBtn->WidgetStyle = MyCoreStyle::Get().GetWidgetStyle<FButtonStyle>(ButtonsStyle);
	}
	if (MyButtons)
	{
		MyButtons->WidgetStyle = MyCoreStyle::Get().GetWidgetStyle<FRadioButtonsStyle>(RadioButtonsStyle);
	}

}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (NewGameBtn)
	{
		NewGameBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::OnNewGameClicked);
		NewGameBtn->OnHovered.AddDynamic(this, &UMainMenuWidget::OnNewGameHovered);
	}
	if (ContinueGameBtn)
	{
		ContinueGameBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::OnContinueClicked);
		ContinueGameBtn->OnHovered.AddDynamic(this, &UMainMenuWidget::OnContinueHovered);
	}
	if (OptionsBtn)
	{
		OptionsBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::OnOptionsClicked);
		OptionsBtn->OnHovered.AddDynamic(this, &UMainMenuWidget::OnOptionsHovered);
	}
	if (SaveGameBtn)
	{
		SaveGameBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::OnSaveGameClicked);
		SaveGameBtn->OnHovered.AddDynamic(this, &UMainMenuWidget::OnSaveGameHovered);
	}
	if (ExitGameBtn)
	{
		ExitGameBtn->OnClicked.AddDynamic(this, &UMainMenuWidget::OnExitGameClicked);
		ExitGameBtn->OnHovered.AddDynamic(this, &UMainMenuWidget::OnExitGameHovered);
	}
	//if (RadioButtonsHost)
	//{
	//	RadioButtonsHost->SetContent(SNew(SRadioButtonsList));
	//}
}

void UMainMenuWidget::OnNewGameClicked()
{

}

void UMainMenuWidget::OnNewGameHovered()
{
	PlayAnimation(NewGameAnimation, 0, 1, EUMGSequencePlayMode::PingPong, 1, false);
}

void UMainMenuWidget::OnContinueClicked()
{

}

void UMainMenuWidget::OnContinueHovered()
{
	PlayAnimation(ContinueGameAnimation, 0, 1, EUMGSequencePlayMode::PingPong, 1, false);
}

void UMainMenuWidget::OnOptionsClicked()
{

}

void UMainMenuWidget::OnOptionsHovered()
{
	PlayAnimation(OptionsAnimation, 0, 1, EUMGSequencePlayMode::PingPong, 1, false);
}

void UMainMenuWidget::OnSaveGameClicked()
{

}

void UMainMenuWidget::OnSaveGameHovered()
{
	PlayAnimation(SaveGameAnimation, 0, 1, EUMGSequencePlayMode::PingPong, 1, false);
	PlayAnimation(ArrowsAnimation, 0, 1, EUMGSequencePlayMode::PingPong, 1, false);
}

void UMainMenuWidget::OnExitGameClicked()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}

void UMainMenuWidget::OnExitGameHovered()
{
	PlayAnimation(ExitGameAnimation, 0, 1, EUMGSequencePlayMode::PingPong, 1, false);
}


void UMainMenuWidget::NativeDestruct()
{
	if (NewGameBtn)
	{
		NewGameBtn->OnPressed.RemoveAll(this);
	}
	if (ContinueGameBtn)
	{
		ContinueGameBtn->OnPressed.RemoveAll(this);
	}
	if (OptionsBtn)
	{
		OptionsBtn->OnPressed.RemoveAll(this);
	}
	if (SaveGameBtn)
	{
		SaveGameBtn->OnPressed.RemoveAll(this);
	}
	if (ExitGameBtn)
	{
		ExitGameBtn->OnPressed.RemoveAll(this);
	}
}