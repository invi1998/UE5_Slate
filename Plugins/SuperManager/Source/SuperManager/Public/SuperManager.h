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

	void FixUpRedirectors();	// 修复重定向器

private:


// 内容浏览器菜单扩展器
#pragma region ContentBrowserMenuExtender

	TSharedRef<FExtender> OnExtendContentBrowserPathViewMenu(const TArray<FString>& SelectedPaths);	// 扩展内容浏览器路径视图菜单
	
	void InitCBMenuExtender();	// 初始化内容浏览器菜单扩展器

	void OnAddCBMenuEntry(FMenuBuilder& MenuBuilder);	// 添加内容浏览器菜单项

	void OnDeleteUnusedAssetsButtonClicked();	// 删除未使用的资产按钮点击事件

	void OnDeleteEmptyFoldersButtonClicked();	// 删除空文件夹按钮点击事件

	TArray<FString> SelectedFolderPaths;	// 选中的文件夹路径

	void OnAdvanceDeletionButtonClicked();	// 高级删除按钮点击事件

#pragma endregion


// 资产工具模块
#pragma region CustomEditorTabs

	void RegisterAdvancedDeletionTabSpawner();	// 注册高级删除选项卡生成器

	TSharedRef<SDockTab>  OnSpawnAdvancedDeletionTab(const FSpawnTabArgs& Args);	// 生成高级删除选项卡

	FName AdvancedDeletionTabIdName = "AdvancedDeletionTab";	// 高级删除选项卡名称

	TArray<TSharedPtr<FAssetData>> GetAllAssetDatasUnderSelectedFolder();	// 获取此文件夹下的所有资产数据

#pragma endregion


// 关卡编辑器菜单扩展器
#pragma region LevelEditorMenuExtender

	void OnLockActorSelectionButtonClicked() const;	// 锁定Actor选择按钮点击事件
	void OnUnlockActorSelectionButtonClicked() const;	// 解锁Actor选择按钮点击事件
	void OnAddLevelEditorMenuEntry(class FMenuBuilder& MenuBuilder) const;	// 添加关卡编辑器菜单项
	TSharedRef<FExtender> CustomLevelEditorMenuExtender(const TSharedRef<FUICommandList> UICommandList, const TArray<AActor*> SelectedActors);	// 自定义关卡编辑器菜单扩展器

	void InitLevelEditorMenuExtender();	// 初始化关卡编辑器菜单扩展器

#pragma endregion


// 选择锁定
#pragma region SelectionLock

	void OnActorSelected(UObject* SelectedObject);	// Actor被选中
	void InitCustomSelectionEvents();	// 初始化自定义选择事件

#pragma endregion

public:
// 数据处理
#pragma region ProccessDataForAssetList

	static bool DeleteSingleAsset(const FAssetData& AssetData);	// 删除单个资产
	static bool DeleteAssets(const TArray<FAssetData>& AssetDatas);	// 删除资产
	static void GetUnusedAssets(TArray<TSharedPtr<FAssetData>>& OutArray, const TArray<TSharedPtr<FAssetData>>& AssetDatas);	// 获取未使用的资产
	static void SyncCBToClickedForAssetList(const FString& AssetPath);	// 同步内容浏览器到点击的资产列表

#pragma endregion

};
