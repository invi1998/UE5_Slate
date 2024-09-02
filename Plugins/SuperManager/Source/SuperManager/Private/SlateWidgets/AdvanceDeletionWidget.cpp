// Copyright INVI_1998


#include "SlateWidgets/AdvanceDeletionWidget.h"

void SAdvanceDeletionTab::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;	// 设置焦点

	ChildSlot
		[
			SNew(STextBlock)
				.Text(FText::FromString(InArgs._TestString))
		];
}
