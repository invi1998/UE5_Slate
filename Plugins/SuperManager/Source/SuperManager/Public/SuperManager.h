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
	void OnExtendContentBrowserPathViewMenu(const TArray<FString>& Strings) const;	// 扩展内容浏览器路径视图菜单
	// ContentBrowserMenuExtender
	void InitCBMenuExtender();	// 初始化内容浏览器菜单扩展器

#pragma endregion

};
