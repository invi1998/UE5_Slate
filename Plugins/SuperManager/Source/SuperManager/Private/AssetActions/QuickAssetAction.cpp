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

	TArray<FAssetData> SelectedAssets = UEditorUtilityLibrary::GetSelectedAssetData();	// 获取选中的资源
	if (SelectedAssets.Num() == 0)
	{
		PrintDebug("No assets selected", FColor::Red);
		PrintLog("No assets selected");
		return;
	}

	uint32 NumDuplicatedAssets = 0;

	for (const FAssetData& Asset : SelectedAssets)
	{
		for (int32 i = 0; i < NumCopies; ++i)
		{
			FString SourceAssetPath = Asset.GetSoftObjectPath().ToString();		// 获取资源路径
			FString NewAssetName = Asset.AssetName.ToString() + FString::Printf(TEXT("_Copy%d"), i+1);	// 新资源名称
			FString NewAssetPathName = FPaths::Combine(Asset.PackagePath.ToString(), NewAssetName);	// 新资源路径

			FAssetData NewAsset = UEditorAssetLibrary::DuplicateAsset(SourceAssetPath, NewAssetPathName);	// 复制资源
			if (NewAsset.IsValid())
			{
				UEditorAssetLibrary::SaveAsset(NewAssetPathName, false);	// 保存资源
				++NumDuplicatedAssets;

				PrintDebug(FString::Printf(TEXT("Duplicated asset: %s"), *NewAsset.AssetName.ToString()), FColor::Green);
				PrintLog(FString::Printf(TEXT("Duplicated asset: %s"), *NewAsset.AssetName.ToString()));
			}
			else
			{
				PrintDebug(FString::Printf(TEXT("Failed to duplicate asset: %s"), *Asset.AssetName.ToString()), FColor::Red);
				PrintLog(FString::Printf(TEXT("Failed to duplicate asset: %s"), *Asset.AssetName.ToString()));
			}
		}
	}

	if (NumDuplicatedAssets > 0)
	{
		PrintDebug(FString::Printf(TEXT("Duplicated %d assets"), NumDuplicatedAssets), FColor::Green);
		PrintLog(FString::Printf(TEXT("Duplicated %d assets"), NumDuplicatedAssets));
	}
	else
	{
		PrintDebug("No assets duplicated", FColor::Red);
		PrintLog("No assets duplicated");
	}
}
