// Copyright INVI_1998

#include "SlateBasics.h"
#include "SlateWidgets/AdvanceDeletionWidget.h"

void SAdvanceDeletionTab::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;	// 设置焦点

	AssetDataUnderSelectedFolder = InArgs._AssetDataList;	// 获取选中文件夹下的资产数据

	FSlateFontInfo TitleFontInfo = FCoreStyle::Get().GetFontStyle("EmbossedText");
	TitleFontInfo.Size = 24;

	FSlateFontInfo NormalFontInfo = FCoreStyle::Get().GetFontStyle("EmbossedText");
	NormalFontInfo.Size = 16;

	FSlateFontInfo SmallFontInfo = FCoreStyle::Get().GetFontStyle("EmbossedText");
	SmallFontInfo.Size = 12;

	ChildSlot
		[
			// 垂直布局
			SNew(SVerticalBox)

				// 第一行 （标题）
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(STextBlock)
						.Text(FText::FromString("Advance Deletion"))
						.Font(TitleFontInfo)
						.Justification(ETextJustify::Center)
						.ColorAndOpacity(FLinearColor::White)
				]

				// 第二行 （下拉菜单，用于筛选资产）
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)

						+ SHorizontalBox::Slot()
						.AutoWidth()
						[
							SNew(STextBlock)
								.Text(FText::FromString("Asset Type:"))
								.Font(NormalFontInfo)
								.Justification(ETextJustify::Left)
								.ColorAndOpacity(FLinearColor::White)
						]
				]


				// 第三行 （实际的资产列表，用于显示资产，滚动条）
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SScrollBox)
						.Orientation(Orient_Vertical)
						.ScrollBarAlwaysVisible(true)
						+ SScrollBox::Slot()
				]

				// 第四行 （底部按钮，用于执行删除操作）
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)

						+ SHorizontalBox::Slot()
						.AutoWidth()
						[
							SNew(SButton)
								.Text(FText::FromString("Delete"))
						]
				]
		];
}
