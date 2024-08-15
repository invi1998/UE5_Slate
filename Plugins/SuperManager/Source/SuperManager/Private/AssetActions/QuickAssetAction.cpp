// Copyright INVI_1998


#include "AssetActions/QuickAssetAction.h"
#include "DebugHeader.h"
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"


void UQuickAssetAction::DuplicateSelectedAssets(int32 NumCopies)
{
	if (NumCopies <= 0)
	{
		PrintDebug("Invalid number of copies", FColor::Red);
		PrintLog("Invalid number of copies");
		return;
	}

	TArray<FAssetData> SelectedAssets = UEditorUtilityLibrary::GetSelectedAssetData();
	if (SelectedAssets.Num() == 0)
	{
		PrintDebug("No assets selected", FColor::Red);
		PrintLog("No assets selected");
		return;
	}

	for (FAssetData Asset : SelectedAssets)
	{
		FString AssetPath = Asset.ObjectPath.ToString();
		FString AssetName = Asset.AssetName.ToString();
		FString AssetClass = Asset.AssetClass.ToString();
		FString AssetPackage = Asset.PackageName.ToString();

		PrintDebug("AssetPath: " + AssetPath, FColor::Green);
		PrintDebug("AssetName: " + AssetName, FColor::Green);
		PrintDebug("AssetClass: " + AssetClass, FColor::Green);
		PrintDebug("AssetPackage: " + AssetPackage, FColor::Green);

		FString NewAssetName = AssetName + "_Copy";
		FString NewAssetPath = AssetPackage + "/" + NewAssetName;

		PrintDebug("NewAssetName: " + NewAssetName, FColor::Green);
		PrintDebug("NewAssetPath: " + NewAssetPath, FColor::Green);

		FAssetData NewAsset = UEditorAssetLibrary::DuplicateAsset(AssetPath, NewAssetPath);
		if (NewAsset.IsValid())
		{
			PrintDebug("Asset duplicated successfully", FColor::Green);
			PrintLog("Asset duplicated successfully");
		}
		else
		{
			PrintDebug("Failed to duplicate asset", FColor::Red);
			PrintLog("Failed to duplicate asset");
		}
	}
}
