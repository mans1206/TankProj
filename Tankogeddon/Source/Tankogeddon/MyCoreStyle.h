// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Slate.h"

/**
 * 
 */
class TANKOGEDDON_API MyCoreStyle
{
public:
	
	static void Initialize();

	static void Shutdown();

	static const ISlateStyle& Get();

private:

	static TSharedPtr<ISlateStyle> StylePtr;

};
