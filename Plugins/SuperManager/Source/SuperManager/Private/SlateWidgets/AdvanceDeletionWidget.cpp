// Copyright INVI_1998


#include "SlateWidgets/AdvanceDeletionWidget.h"

void SAdvanceDeletionTab::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;	// 设置焦点

	FSlateFontInfo TitleFontInfo = FCoreStyle::Get().GetFontStyle("EmbossedText");
	TitleFontInfo.Size = 24;

	ChildSlot
		[
			// 垂直布局
			SNew(SVerticalBox)

				// 第一行
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(STextBlock)
						.Text(FText::FromString("Advance Deletion"))
						.Font(TitleFontInfo)
						.Justification(ETextJustify::Center)
						.ColorAndOpacity(FLinearColor::White)
				]
		];
}
