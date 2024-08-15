// Copyright INVI_1998

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
//
//代码在 5.0 之后为了修复重定向器发生了很大变化。以下是虚幻引擎在 5.4 及以上版本中用于修复重定向器的最新版本：
//首先，您需要这些包含项：
#include "AssetToolsModule.h"
#include "AssetViewUtils.h"
#include "AssetRegistry/AssetRegistryModule.h"

#include "QuickAssetAction.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMANAGER_API UQuickAssetAction : public UAssetActionUtility
{
	GENERATED_BODY()

public:
	UFUNCTION(CallInEditor)
	static void TestFunc();
	
};
