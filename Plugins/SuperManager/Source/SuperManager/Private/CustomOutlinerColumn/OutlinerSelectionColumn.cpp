// Copyright INVI_1998


#include "CustomOutlinerColumn/OutlinerSelectionColumn.h"
#include "CustomStyle/SuperManagerStyle.h"

#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "FSuperManagerModule"

FOutlinerSelectionColumn::FOutlinerSelectionColumn(ISceneOutliner& SceneOutliner)
{
}

FName FOutlinerSelectionColumn::GetColumnID()
{
	return "SelectionLock";
}

FName FOutlinerSelectionColumn::GetID()
{
	return "SelectionLock";
}

SHeaderRow::FColumn::FArguments FOutlinerSelectionColumn::ConstructHeaderRowColumn()
{
	SHeaderRow::FColumn::FArguments Args = SHeaderRow::Column(GetColumnID())
		.HAlignHeader(HAlign_Center)
		.VAlignHeader(VAlign_Center)
		.HAlignCell(HAlign_Center)
		.VAlignCell(VAlign_Center)
		.FixedWidth(24.0f)
		.DefaultTooltip(LOCTEXT("Actor Selection Lock - Press icon to lock or unlock actor selection", "Acotr锁定选择 - 点击图标锁定或解锁Actor选择"))
		[
			SNew(SImage)
				.ColorAndOpacity(FSlateColor::UseForeground())
				.Image(FSuperManagerStyle::GetSlateStyleSet()->GetBrush("ContentBrowser.SelectionLock"))
		];

	return Args;
}

const TSharedRef<SWidget> FOutlinerSelectionColumn::ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row)
{
	return SNew(SBox)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.Padding(2.0f);
}

#undef LOCTEXT_NAMESPACE
