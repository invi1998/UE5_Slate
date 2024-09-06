// Copyright INVI_1998


#include "AssetActions/QuickMaterialCreationWidget.h"
#include "DebugHeader.h"

#pragma region QuickMaterialCreationCore

void UQuickMaterialCreationWidget::CreateMaterialFromSelectedTextures()
{
	if (bUserSetMaterialName)
	{
		if (MaterialName.IsEmpty())
		{
			SM_Debug::ShowMessageDialog(FText::FromString("Material Name is Empty!"), FText::FromString("Error"), EAppMsgType::Ok);
			return;
		}
	}
}

#pragma endregion
