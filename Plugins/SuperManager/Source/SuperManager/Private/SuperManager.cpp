// Copyright Epic Games, Inc. All Rights Reserved.

#include "SuperManager.h"

#include "ContentBrowserDelegates.h"
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

void FSuperManagerModule::OnExtendContentBrowserPathViewMenu(const TArray<FString>& Strings) const
{
}

void FSuperManagerModule::InitCBMenuExtender()
{
	FContentBrowserModule ContentBrowser = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");	// 加载内容浏览器模块

	// 添加内容浏览器路径视图菜单扩展器
	TArray<FContentBrowserMenuExtender_SelectedPaths>& ContentBrowserExtenders = ContentBrowser.GetAllPathViewContextMenuExtenders();
	ContentBrowserExtenders.Add(FContentBrowserMenuExtender_SelectedPaths::CreateRaw(this, &FSuperManagerModule::OnExtendContentBrowserPathViewMenu));

}

##pragma endregion

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSuperManagerModule, SuperManager)