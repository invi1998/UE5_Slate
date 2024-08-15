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

第一个，函数，资产复制