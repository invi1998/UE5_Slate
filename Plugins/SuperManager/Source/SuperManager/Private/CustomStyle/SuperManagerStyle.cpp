// Copyright INVI_1998


#include "CustomStyle/SuperManagerStyle.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

FName FSuperManagerStyle::StyleSetName = TEXT("SuperManagerStyle");
TSharedPtr<FSlateStyleSet> FSuperManagerStyle::CustomSlateStyleSet = nullptr;

void FSuperManagerStyle::InitializeIcons()
{
	if (!CustomSlateStyleSet.IsValid())
	{
		CustomSlateStyleSet = CreateSlateStyleSet();
	}

	if (!FSlateStyleRegistry::FindSlateStyle(StyleSetName))
	{
		FSlateStyleRegistry::RegisterSlateStyle(*CustomSlateStyleSet);
	}
}

void FSuperManagerStyle::Shutdown()
{
	if (CustomSlateStyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*CustomSlateStyleSet);
		CustomSlateStyleSet.Reset();
	}
}

TSharedRef<FSlateStyleSet> FSuperManagerStyle::GetSlateStyleSet()
{
	return CustomSlateStyleSet.ToSharedRef();
}

TSharedRef<FSlateStyleSet> FSuperManagerStyle::CreateSlateStyleSet()
{
	TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet(StyleSetName));

	IPluginManager& PluginManager = IPluginManager::Get();

	const FString IconDir = PluginManager.FindPlugin(TEXT("SuperManager"))->GetBaseDir() / TEXT("Resources");

	Style->Set("ContentBrowser.DeleteUnusedAssets", new FSlateImageBrush(IconDir / TEXT("DeleteUnusedAsset.png"), FVector2D(16.0f, 16.0f)));
	Style->Set("ContentBrowser.DeleteEmptyFolders", new FSlateImageBrush(IconDir / TEXT("DeleteEmptyFolders.png"), FVector2D(16.0f, 16.0f)));
	Style->Set("ContentBrowser.AdvanceDeletion", new FSlateImageBrush(IconDir / TEXT("AdvanceDeletion.png"), FVector2D(16.0f, 16.0f)));
	Style->Set("ContentBrowser.SelectionLock", new FSlateImageBrush(IconDir / TEXT("SelectionLock.png"), FVector2D(16.0f, 16.0f)));
	Style->Set("ContentBrowser.SelectionUnlock", new FSlateImageBrush(IconDir / TEXT("SelectionUnlock.png"), FVector2D(16.0f, 16.0f)));

	return Style;
}
