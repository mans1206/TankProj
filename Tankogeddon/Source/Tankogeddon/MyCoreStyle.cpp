// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCoreStyle.h"
#include "Engine.h"
#include "SlateBasics.h"
#include "Slate/SlateGameResources.h"
#include "Styling/ISlateStyle.h"

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush(Style->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)

TSharedPtr<ISlateStyle> MyCoreStyle::StylePtr;

TSharedPtr<ISlateStyle> CreateStyle()
{
	const FString ScopeToDirectory("/Game/Styles");
	TSharedPtr<ISlateStyle> Style = FSlateGameResources::New(FName("MyCoreStyle"), ScopeToDirectory, ScopeToDirectory);

	//FString Path = FPaths::ProjectContentDir() / TEXT("/Game/Styles");
	////FString Path = "/Game/UI";
	//TSharedPtr<FSlateStyleSet> Style = FSlateGameResources::New(FName("MyCoreStyle"), Path, Path);

	//Style->Set("Red", FLinearColor::Red);
	//Style->Set("DefaultPadding", FMargin(5.f));
	//Style->Set("Wolf", new IMAGE_BRUSH("wolf", FVector2D(256.f)));

	return Style;
}

void MyCoreStyle::Initialize()
{
	Shutdown();

	StylePtr = CreateStyle();
	FSlateStyleRegistry::RegisterSlateStyle(*StylePtr);
}

void MyCoreStyle::Shutdown()
{
	if (StylePtr.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StylePtr);
		StylePtr.Reset();
	}
}

const ISlateStyle& MyCoreStyle::Get()
{
	if (!StylePtr.IsValid())
	{
		Initialize();
	}
	return *StylePtr;
}
