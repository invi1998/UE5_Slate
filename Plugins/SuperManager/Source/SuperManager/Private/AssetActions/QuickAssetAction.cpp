// Copyright INVI_1998


#include "AssetActions/QuickAssetAction.h"

void UQuickAssetAction::TestFunc()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("TestFunc: Working"));
	}
}
