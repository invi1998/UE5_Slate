// Copyright Epic Games, Inc. All Rights Reserved.

#include "SuperManager.h"

#include "ContentBrowserModule.h"

#define LOCTEXT_NAMESPACE "FSuperManagerModule"

void FSuperManagerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	InitCBMenuExtender();
}

void FSuperManagerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}



#pragma region ContentBrowserMenuExtender

TSharedRef<FExtender> FSuperManagerModule::OnExtendContentBrowserPathViewMenu(const TArray<FString>& SelectedPaths)
{
	TSharedRef<FExtender> Extender(new FExtender);

	if (SelectedPaths.Num() > 0)
	{
		// 添加菜单项
		Extender->AddMenuExtension(
			"Delete",		// 在内容浏览器路径视图菜单中的位置
			EExtensionHook::After,		// 在Delete菜单项之后添加
			TSharedPtr<FUICommandList>(),	//
			FMenuExtensionDelegate::CreateRaw(this, &FSuperManagerModule::OnAddCBMenuEntry)	// 添加菜单项的委托方法
		);
	}

	return Extender;
}

void FSuperManagerModule::InitCBMenuExtender()
{
	FContentBrowserModule& ContentBrowser = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");	// 加载内容浏览器模块

	// 添加内容浏览器路径视图菜单扩展器
	TArray<FContentBrowserMenuExtender_SelectedPaths>& ContentBrowserExtenders = ContentBrowser.GetAllPathViewContextMenuExtenders();

	// CreateRaw 创建代理对象，同时绑定委托方法（等同于先创建代理对象，再绑定委托方法）
	// CreateRaw 用于创建一个新的 TSharedRef<FContentBrowserMenuExtender_SelectedPaths> 对象，同时绑定 OnExtendContentBrowserPathViewMenu 方法
	ContentBrowserExtenders.Add(FContentBrowserMenuExtender_SelectedPaths::CreateRaw(this, &FSuperManagerModule::OnExtendContentBrowserPathViewMenu));

}

void FSuperManagerModule::OnAddCBMenuEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		LOCTEXT("Delete Unused Assets", "删除未使用的资产"),
		LOCTEXT("Safely Delete", "安全删除当前文件夹下所有未使用到的资产"),
		FSlateIcon(),
		FExecuteAction::CreateRaw(this, &FSuperManagerModule::OnDeleteUnusedAssetsButtonClicked)
	);
}

void FSuperManagerModule::OnDeleteUnusedAssetsButtonClicked()
{
	// 删除未使用的资产按钮点击事件
}

#pragma endregion

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSuperManagerModule, SuperManager)