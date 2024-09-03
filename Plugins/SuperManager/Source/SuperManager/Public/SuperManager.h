// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FSuperManagerModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:


// 内容浏览器菜单扩展器
#pragma region ContentBrowserMenuExtender

	TSharedRef<FExtender> OnExtendContentBrowserPathViewMenu(const TArray<FString>& SelectedPaths);	// 扩展内容浏览器路径视图菜单
	
	void InitCBMenuExtender();	// 初始化内容浏览器菜单扩展器

	void OnAddCBMenuEntry(FMenuBuilder& MenuBuilder);	// 添加内容浏览器菜单项

	void OnDeleteUnusedAssetsButtonClicked();	// 删除未使用的资产按钮点击事件

	void OnDeleteEmptyFoldersButtonClicked();	// 删除空文件夹按钮点击事件

	TArray<FString> SelectedFolderPaths;	// 选中的文件夹路径

	void FixUpRedirectors();	// 修复重定向器

	void OnAdvanceDeletionButtonClicked();	// 高级删除按钮点击事件

#pragma endregion


// 资产工具模块
#pragma region CustomEditorTabs

	void RegisterAdvancedDeletionTabSpawner();	// 注册高级删除选项卡生成器

	TSharedRef<SDockTab>  OnSpawnAdvancedDeletionTab(const FSpawnTabArgs& Args);	// 生成高级删除选项卡

	FName AdvancedDeletionTabIdName = "AdvancedDeletionTab";	// 高级删除选项卡名称

	TArray<TSharedPtr<FAssetData>> GetAllAssetDatasUnderSelectedFolder();	// 获取此文件夹下的所有资产数据

#pragma endregion

public:
#pragma region ProccessDataForAssetList

	bool DeleteSingleAsset(const FAssetData& AssetData);	// 删除单个资产
	bool DeleteAssets(const TArray<FAssetData>& AssetDatas);	// 删除资产
	void GetUnusedAssets(TArray<TSharedPtr<FAssetData>>& OutArray, const TArray<TSharedPtr<FAssetData>>& AssetDatas);	// 获取未使用的资产

#pragma endregion

};
