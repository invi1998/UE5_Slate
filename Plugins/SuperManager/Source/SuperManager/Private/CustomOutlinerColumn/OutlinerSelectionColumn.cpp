// Copyright INVI_1998


#include "CustomOutlinerColumn/OutlinerSelectionColumn.h"


FOutlinerSelectionColumn::FOutlinerSelectionColumn(ISceneOutliner& SceneOutliner)
{
}

FName FOutlinerSelectionColumn::GetColumnID()
{
	return "Selection";
}

SHeaderRow::FColumn::FArguments FOutlinerSelectionColumn::ConstructHeaderRowColumn()
{
	return SHeaderRow::Column(GetColumnID())
		.DefaultLabel(NSLOCTEXT("SceneOutliner", "SelectionColumnHeader", "Selection"))
		.FixedWidth(24.0f);
}

const TSharedRef<SWidget> FOutlinerSelectionColumn::ConstructRowWidget(FSceneOutlinerTreeItemRef TreeItem, const STableRow<FSceneOutlinerTreeItemPtr>& Row)
{
	return SNew(SBox)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.Padding(2.0f)
		[
			SNew(SCheckBox)
			.IsChecked_Lambda([TreeItem]()
			{
				return TreeItem->IsSelected() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
			})
			.OnCheckStateChanged_Lambda([TreeItem](ECheckBoxState NewState)
			{
				TreeItem->SetSelectionState(NewState == ECheckBoxState::Checked);
			})
		];
}
