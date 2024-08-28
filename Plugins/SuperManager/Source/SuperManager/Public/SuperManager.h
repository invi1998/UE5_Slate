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

#pragma endregion

};
