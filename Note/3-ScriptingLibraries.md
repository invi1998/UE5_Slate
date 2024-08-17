# Scripting Libraries

包含头文件

```c++
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"
```

EditorAssetLibrary 需要包含依赖在CS中

```c++
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore", 
                "EditorScriptingUtilities",		// EditorAssetLibrary 需要包含依赖在CS中
				// ... add private dependencies that you statically link with here ...	
			}
			);
```



我们第一个自定义编辑器功能，就是实现资产的批量复制，为了实现这点，我们需要使用到EditorAssetLibrary函数库里的功能

```c++

	/**
	 * Duplicate an asset from the Content Browser. Will try to checkout the file. The Asset will be loaded before being duplicated.
	 * @param	SourceAssetPath			Asset Path of the asset that we want to copy from.
	 * @param	DestinationAssetPath	Asset Path of the duplicated asset.
	 * @return	The duplicated object if the operation succeeds.
	 */
	UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Asset")
	static UObject* DuplicateAsset(const FString& SourceAssetPath, const FString& DestinationAssetPath);

```



## 第一个函数，资产复制

```c++
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

```

