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
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Center)
						.FillWidth(0.2)
						[
							SNew(STextBlock)
								.Text(FText::FromString("Asset Type:"))
								.Font(NormalFontInfo)
								.Justification(ETextJustify::Left)
								.ColorAndOpacity(FLinearColor::White)
						]

						+ SHorizontalBox::Slot()
						.AutoWidth()
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Center)
						.FillWidth(0.8)
						[
							SNew(SHorizontalBox)

								+ SHorizontalBox::Slot()
								.AutoWidth()
								.HAlign(HAlign_Right)
								.VAlign(VAlign_Center)
								.Padding(5.f)
								[
									OnGenerateSelectAllToggleButton()
								]

								+ SHorizontalBox::Slot()
								.AutoWidth()
								.HAlign(HAlign_Right)
								.VAlign(VAlign_Center)
								.Padding(5.f)
								[
									OnGenerateDeleteSelectedButton()
								]
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

#pragma region RowWidgetsForAssetListViews

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
				.Padding(5.f)
				[
					OnGenerateCheckBox(Item)
				]

				// 第二列：资产类型（资产类名）
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
				.FillWidth(0.45)
				[
					OnGenerateTextBlockForRowWidget(Item->AssetClassPath.ToString(), FCoreStyle::Get().GetFontStyle("EmbossedText"))
				]

				// 第三列：资产名称
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
				.FillWidth(0.4)
				[
					OnGenerateTextBlockForRowWidget(Item->AssetName.ToString(), FCoreStyle::Get().GetFontStyle("EmbossedText"))
				]

				// 第四列：资产删除按钮
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				.FillWidth(0.1)
				.Padding(5.f)
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
		{
			if (SelectedAssetDataList.Contains(Item))
			{
				SelectedAssetDataList.Remove(Item);
			}
			break;
		}
	case ECheckBoxState::Checked:
		{
			if (!SelectedAssetDataList.Contains(Item))
			{
				SelectedAssetDataList.Add(Item);
			}
			break;
		}
	case ECheckBoxState::Undetermined:		// 未确定
		if (SelectedAssetDataList.Contains(Item))
		{
			SelectedAssetDataList.Remove(Item);
		}
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
		.HasDownArrow(true)
		.ButtonStyle(FCoreStyle::Get(), "SimpleButton")
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

#pragma endregion


#pragma region TabButtons

FReply SAdvanceDeletionTab::OnSelectAllButtonClicked()
{
	bIsAllSelected = !bIsAllSelected;

	// 更新按钮文本
	CurrentSelectedToggleButtonText = bIsAllSelected ? FText::FromString("Cancel All") : FText::FromString("Select All");

	if (SelectAllToggleButton.IsValid())
	{
		const FLinearColor ButtonColor = FLinearColor(195.f / 255.f, 248.f / 255.f, 236.f / 255.f, 1.f);
		SelectAllToggleButton->SetContent(ConstructTextForTabButtons(CurrentSelectedToggleButtonText));
		SelectAllToggleButton->SetColorAndOpacity(bIsAllSelected ? FLinearColor::White : ButtonColor);
	}

	return FReply::Handled();
}

FReply SAdvanceDeletionTab::OnDeleteSelectedButtonClicked()
{
	if (SelectedAssetDataList.Num() <= 0)
	{
		return FReply::Handled();
	}

	FSuperManagerModule& SuperManagerModule = FModuleManager::LoadModuleChecked<FSuperManagerModule>("SuperManager");
	TArray<FAssetData> SelectedAssetDataArray;
	for (const TSharedPtr<FAssetData>& AssetData : SelectedAssetDataList)
	{
		SelectedAssetDataArray.Add(*AssetData.Get());
	}

	if (SuperManagerModule.DeleteAssets(SelectedAssetDataArray))
	{
		// 刷新表格
		for (const TSharedPtr<FAssetData>& AssetData : SelectedAssetDataList)
		{
			if (AssetDataUnderSelectedFolder.Contains(AssetData))
			{
				AssetDataUnderSelectedFolder.Remove(AssetData);
			}
		}

		RefreshAssetListView();
	}


	return FReply::Handled();
}

TSharedRef<SButton> SAdvanceDeletionTab::OnGenerateSelectAllToggleButton()
{
	const FLinearColor ButtonColor = FLinearColor(195.f / 255.f, 248.f / 255.f, 236.f / 255.f, 1.f);
	TSharedRef<SButton> Button = SNew(SButton)
		.ContentPadding(FMargin(5.f))
		.ButtonColorAndOpacity(FLinearColor::Green)
		.OnClicked(this, &SAdvanceDeletionTab::OnSelectAllButtonClicked);

	CurrentSelectedToggleButtonText = bIsAllSelected ? FText::FromString("Cancel All") : FText::FromString("Select All");

	Button->SetContent(ConstructTextForTabButtons(CurrentSelectedToggleButtonText));
	Button->SetColorAndOpacity(bIsAllSelected ? FLinearColor::White : ButtonColor);

	SelectAllToggleButton = Button.ToSharedPtr();

	return Button;
}

TSharedRef<SButton> SAdvanceDeletionTab::OnGenerateDeleteSelectedButton()
{
	TSharedRef<SButton> Button = SNew(SButton)
		.ContentPadding(FMargin(5.f))
		.ButtonColorAndOpacity(FLinearColor::Red)
		.OnClicked(this, &SAdvanceDeletionTab::OnDeleteSelectedButtonClicked);

	Button->SetContent(ConstructTextForTabButtons(FText::FromString("Delete Selected")));

	return Button;
}

TSharedRef<STextBlock> SAdvanceDeletionTab::ConstructTextForTabButtons(const FText& TextContent)
{
	FSlateFontInfo FontInfo = FCoreStyle::Get().GetFontStyle("EmbossedText");
	FontInfo.Size = 16;

	TSharedRef<STextBlock> TextBlock = SNew(STextBlock)
		.Text(TextContent)
		.Font(FontInfo)
		.Justification(ETextJustify::Center)
		.ColorAndOpacity(FLinearColor::White);

	return TextBlock;
}

#pragma endregion

