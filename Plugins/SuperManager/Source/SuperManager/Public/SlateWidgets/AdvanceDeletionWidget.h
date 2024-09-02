// Copyright INVI_1998

#pragma once

#include "Widgets/SCompoundWidget.h"

// 定义一个数据模型，用于存储下拉框中的选项
struct FDropdownOption
{
	FText DisplayText;
	FString Value;

	FDropdownOption(const FText& InDisplayText, const FString& InValue)
		: DisplayText(InDisplayText), Value(InValue)
	{}

	bool operator==(const FDropdownOption& Other) const
	{
		return Value == Other.Value;
	}
};

class SAdvanceDeletionTab : public SCompoundWidget
{


	// SLATE_BEGIN_ARGS 是一个宏，用于定义构造函数的参数列表
	SLATE_BEGIN_ARGS(SAdvanceDeletionTab) {}

	// SLATE_ARGUMENT 宏用于定义构造函数的参数
	SLATE_ARGUMENT(TArray<TSharedPtr<FAssetData>>, AssetDataList)

	SLATE_END_ARGS()

public:
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	TArray<TSharedPtr<FAssetData>> AssetDataUnderSelectedFolder;	// 选中文件夹下的资产数据

	// 生成资产列表的行
	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FAssetData> Item, const TSharedRef<STableViewBase>& OwnerTable);

	TSharedRef<SCheckBox> OnGenerateCheckBox(const TSharedPtr<FAssetData>& Item);

	void OnCheckBoxStateChanged(ECheckBoxState NewState, TSharedPtr<FAssetData> Item);

	TSharedRef<STextBlock> OnGenerateTextBlockForRowWidget(const FString& TextContent, const FSlateFontInfo& FontInfo);

	FReply OnRowDeleteButtonClicked(TSharedPtr<FAssetData> AssetData);

	TSharedRef<SButton> OnGenerateButtonForRowWidget(const TSharedPtr<FAssetData>& Item);

	TSharedRef<SComboButton> OnGenerateCutPagesComboBox();

	TSharedRef<SButton> OnGenerateNoBorderButton(const FText& ButtonText);

	int32 CurrentPage = 1;	// 当前页码

	int32 OnePageCount = 10;	// 每页显示数量
};

