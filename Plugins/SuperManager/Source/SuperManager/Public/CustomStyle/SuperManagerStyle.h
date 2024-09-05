// Copyright INVI_1998

#pragma once

#include "Styling/SlateStyle.h"

class FSuperManagerStyle
{

public:
	static void InitializeIcons();

	static void Shutdown();

private:
	static FName StyleSetName;

	static TSharedRef<FSlateStyleSet> CreateSlateStyleSet();
	static TSharedPtr<FSlateStyleSet> CustomSlateStyleSet;
	
};
