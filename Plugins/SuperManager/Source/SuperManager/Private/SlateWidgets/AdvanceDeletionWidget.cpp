// Copyright INVI_1998

#include "SlateWidgets/AdvanceDeletionWidget.h"

#include "SlateBasics.h"
#include "DebugHeader.h"
#include "SuperManager.h"


void SAdvanceDeletionTab::Construct(const FArguments& InArgs)
{
	bCanSupportFocus = true;	// 设置焦点

	AssetDataUnderSelectedFolder = InArgs._AssetDataList;	// 获取选中文件夹下的资产数据

	FSlateFontInfo TitleFontInfo = FCoreStyle::Get().GetFontStyle("EmbossedText");
	TitleFontInfo.Size = 24;

	FSlateFontInfo NormalFontInfo = FCoreStyle::Get().GetFontStyle("EmbossedText");
	NormalFontInfo.Size = 16;

	FSlateFontInfo SmallFontInfo = FCoreStyle::Get().GetFontStyle("EmbossedText");
	SmallFontInfo.Size = 8;

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
				.VAlign(VAlign_Fill)		// 垂直填充
				[
					SNew(SScrollBox)
						.Orientation(Orient_Vertical)
						.ScrollBarAlwaysVisible(false)
						+ SScrollBox::Slot()
						[
							OnConstructAssetListView()
						]
				]

				// 第四行 （显示资产数量，显示分页按钮，前往第一页，前往上一页，前往下一页，前往最后一页）
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)

						+ SHorizontalBox::Slot()
						.AutoWidth()
						[
							SNew(STextBlock)
								.Text(FText::FromString("Total: " + FString::FromInt(AssetDataUnderSelectedFolder.Num())))
								.Font(SmallFontInfo)
								.Justification(ETextJustify::Left)
								.ColorAndOpacity(FLinearColor::White)
						]

						+ SHorizontalBox::Slot()
						.AutoWidth()
						[
							OnGenerateCutPagesComboBox()
						]
				]

				// 第五行 （底部按钮，用于执行删除操作）
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

TSharedRef<SListView<TSharedPtr<FAssetData>>> SAdvanceDeletionTab::OnConstructAssetListView()
{
	ConstructedAssetListView = SNew(SListView<TSharedPtr<FAssetData>>)
		.ItemHeight(24)
		.ListItemsSource(&AssetDataUnderSelectedFolder)
		.OnGenerateRow(this, &SAdvanceDeletionTab::OnGenerateRowForList);

	return ConstructedAssetListView.ToSharedRef();
}

void SAdvanceDeletionTab::RefreshAssetListView()
{
	if (ConstructedAssetListView.IsValid())
	{
		ConstructedAssetListView->RequestListRefresh();
		// ConstructedAssetListView->RebuildList();
	}
	
}

TSharedRef<ITableRow> SAdvanceDeletionTab::OnGenerateRowForList(TSharedPtr<FAssetData> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	if (!Item.IsValid())
	{
		return SNew(STableRow<TSharedPtr<FAssetData>>, OwnerTable);
	}

	TSharedRef<STableRow<TSharedPtr<FAssetData>>> TableRow =
	SNew(STableRow<TSharedPtr<FAssetData>>, OwnerTable)
		[
			// 水平布局
			SNew(SHorizontalBox)

				// 第一列：复选框
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
				.FillWidth(0.05)
				[
					OnGenerateCheckBox(Item)
				]

				// 第二列：资产类型（资产类名）
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Fill)
				.FillWidth(0.45)
				[
					OnGenerateTextBlockForRowWidget(Item->AssetClassPath.ToString(), FCoreStyle::Get().GetFontStyle("EmbossedText"))
				]

				// 第三列：资产名称
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Fill)
				.FillWidth(0.4)
				[
					OnGenerateTextBlockForRowWidget(Item->AssetName.ToString(), FCoreStyle::Get().GetFontStyle("EmbossedText"))
				]

				// 第四列：资产删除按钮
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Fill)
				.FillWidth(0.1)
				[
					OnGenerateButtonForRowWidget(Item)
				]
		];

	return TableRow;
}

TSharedRef<SCheckBox> SAdvanceDeletionTab::OnGenerateCheckBox(const TSharedPtr<FAssetData>& Item)
{
	TSharedRef<SCheckBox> CheckBox = SNew(SCheckBox)
		.Type(ESlateCheckBoxType::CheckBox)
		.IsChecked(ECheckBoxState::Unchecked)
		.Visibility(EVisibility::Visible)
		.OnCheckStateChanged(this, &SAdvanceDeletionTab::OnCheckBoxStateChanged, Item);

	return CheckBox;
}

void SAdvanceDeletionTab::OnCheckBoxStateChanged(ECheckBoxState NewState, TSharedPtr<FAssetData> Item)
{
	switch (NewState)
	{
	case ECheckBoxState::Unchecked:
		SM_Debug::PrintDebug(Item->AssetName.ToString() + " is unchecked.", FColor::Red);
		break;
	case ECheckBoxState::Checked:
		SM_Debug::PrintDebug(Item->AssetName.ToString() + " is checked.", FColor::Green);
		break;
	case ECheckBoxState::Undetermined:
		SM_Debug::PrintDebug(Item->AssetName.ToString() + " is undetermined.", FColor::Yellow);
		break;
	default:
		break;
	}
}

TSharedRef<STextBlock> SAdvanceDeletionTab::OnGenerateTextBlockForRowWidget(const FString& TextContent, const FSlateFontInfo& FontInfo)
{
	TSharedRef<STextBlock> TextBlock = SNew(STextBlock)
		.Text(FText::FromString(TextContent))
		.Font(FontInfo)
		.ColorAndOpacity(FLinearColor::White);

	return TextBlock;
}

FReply SAdvanceDeletionTab::OnRowDeleteButtonClicked(TSharedPtr<FAssetData> AssetData)
{
	FSuperManagerModule& SuperManagerModule = FModuleManager::LoadModuleChecked<FSuperManagerModule>("SuperManager");
	const bool DelRet = SuperManagerModule.DeleteSingleAsset(*AssetData.Get());

	// 刷新表格
	if (DelRet)
	{
		if (AssetDataUnderSelectedFolder.Contains(AssetData))
		{
			AssetDataUnderSelectedFolder.Remove(AssetData);
		}
		
		RefreshAssetListView();
	}

	return FReply::Handled();
}

TSharedRef<SButton> SAdvanceDeletionTab::OnGenerateButtonForRowWidget(const TSharedPtr<FAssetData>& Item)
{
	TSharedRef<SButton> Button = SNew(SButton)
		.Text(FText::FromString("Delete"))
		.OnClicked(this, &SAdvanceDeletionTab::OnRowDeleteButtonClicked, Item);

	return Button;
}

TSharedRef<SComboButton> SAdvanceDeletionTab::OnGenerateCutPagesComboBox()
{
	TSharedRef<SComboButton> ComboButton = SNew(SComboButton)
		.ButtonContent()
		[
			SNew(STextBlock)
				.Text(FText::FromString("10 articles / per page"))
				.Font(FCoreStyle::Get().GetFontStyle("EmbossedText"))
				.ColorAndOpacity(FLinearColor::White)
		]
		.ContentPadding(FMargin(5.0f))
		.MenuContent()
		[
			SNew(SVerticalBox)

				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					OnGenerateNoBorderButton(FText::FromString("10 articles / per page"))
				]

				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					OnGenerateNoBorderButton(FText::FromString("50 articles / per page"))
				]

				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					OnGenerateNoBorderButton(FText::FromString("100 articles / per page"))
				]

				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					OnGenerateNoBorderButton(FText::FromString("All articles / per page"))
				]
		];

	return ComboButton;
}

TSharedRef<SButton> SAdvanceDeletionTab::OnGenerateNoBorderButton(const FText& ButtonText)
{
	TSharedRef<SButton> Button = SNew(SButton)
		.Text(ButtonText)
		.ButtonStyle(FCoreStyle::Get(), "NoBorder")
		.ForegroundColor(FLinearColor::Gray);

	return Button;
}

