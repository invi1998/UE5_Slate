# Custom Editor Message

## MessageDialog & NotificationInfo (消息弹窗和通知消息)

```c++
#include "Widgets/Notifications/SNotificationList.h"
#include "Framework/Notifications/NotificationManager.h"

inline EAppReturnType::Type ShowMessageDialog(const FText& InContent, const FText& InTitle, EAppMsgType::Type InType)
{
	return FMessageDialog::Open(InType, InContent, InTitle);
}

inline void ShowNotifyInfo(const FText& InContent, const FText& InTitle)
{
	FNotificationInfo Info(InTitle);
	Info.bFireAndForget = true;		// 自动消失
	Info.ExpireDuration = 2.0f;		// 显示时间
	Info.bUseLargeFont = true;		// 使用大字体
	Info.bUseThrobber = true;		// 使用加载动画
	Info.bUseSuccessFailIcons = false;	// 使用成功失败图标
	Info.FadeInDuration = 0.5f;		// 淡入时间
	Info.FadeOutDuration = 0.5f;	// 淡出时间

	Info.SubText = InContent;		// 设置内容

	FSlateNotificationManager::Get().AddNotification(Info);	// 添加通知
}
```





# Steps For Custom Menu Entry （自定义菜单入口）

现在，我们的需求是需要在编辑器的菜单项中新增我们插件功能选项。

那么，回到插件模块，入口函数应该就是模块里StartupModule

![image-20240827141742137](.\img\image-20240827141742137.png)

该函数是在加载编辑器的时候被执行，所以这里也是我们初始化插件内容的最好入口。



## PathViewContextMenuExtenders


在Unreal Engine 5（UE5）中，`PathViewContextMenuExtenders` 这个概念与扩展编辑器中的上下文菜单有关。在Unreal Engine中，开发人员可以利用插件或通过C++代码来扩展编辑器的功能，例如添加新的菜单项、工具栏按钮或者是在特定情况下出现的上下文菜单选项。

具体来说，`PathViewContextMenuExtenders` 允许开发者向路径查看器（PathView）的上下文菜单添加自定义选项。路径查看器通常用于显示和操作某些类型的路径数据，比如AI导航路径或者其他类型的路线规划。

要实现这样的功能，开发者需要了解Unreal Engine的模块化系统以及如何注册上下文菜单扩展。这通常涉及到以下步骤：

1. **定义扩展点**：确定你想要扩展的上下文菜单的具体位置。在UE5中，这通常是通过一个定义好的扩展点来完成的。
2. **实现扩展逻辑**：编写代码来响应这个扩展点，并添加自定义的菜单项。这通常会涉及到使用`FContextMenuBuilder`来构建菜单。
3. **注册扩展**：确保你的扩展逻辑在合适的时间被调用。这可以通过在启动时注册一个扩展委托来完成。



## #pragma region

`#pragma region` 是C++预处理器的一个指令，它并不属于C++语言的一部分，而是由编译器厂商提供的扩展。在Unreal Engine 5（UE5）以及其他使用C++的项目中，`#pragma region` 被用来组织代码，使得代码更易于阅读和管理。它本身不产生任何可执行代码，而只是作为一个标记帮助代码编辑器折叠或展开代码区域。

### 使用方法

`#pragma region` 和对应的 `#pragma endregion` 之间的代码会被视为一个区域。你可以给每个区域起一个名字，这个名字在IDE中会显示为折叠后的标题。例如：

```cpp
class MyClass
{
public:
    MyClass();
    ~MyClass();

    void DoSomething();

private:
#pragma region MemberVariables
    int m_iData;
    float m_fData;
#pragma endregion // MemberVariables

#pragma region HelperFunctions
    void DoHelperFunction();
#pragma endregion // HelperFunctions
};
```

在这个例子中，我们创建了两个区域：`MemberVariables` 和 `HelperFunctions`。在支持这一特性的IDE中，比如Visual Studio，你可以点击这些区域名来折叠或展开相应的代码块。

### 注意事项

- 不同的IDE对 `#pragma region` 的支持程度不同。有些IDE可能不支持这种语法，或者支持的方式略有不同。
- 过度使用 `#pragma region` 可能会导致代码结构过于复杂，难以维护。应该谨慎地使用它来组织代码，而不是过度分割代码。
- 在团队协作中，最好确保所有成员使用的IDE都支持 `#pragma region`，以保证一致性。

### 在UE5中的应用

在UE5的源码或项目中，`#pragma region` 同样可以用来组织代码。尤其是在较大的类或头文件中，使用 `#pragma region` 来分隔不同的成员变量、函数声明或其他逻辑部分，可以帮助提高代码的可读性和可维护性。

如果你在使用Visual Studio作为开发环境，那么`#pragma region`将非常有用，因为Visual Studio提供了很好的支持来显示和操作这些区域。然而，在其他环境中，如命令行编译或不同的IDE中，`#pragma region`仅作为注释存在，不会影响代码的行为。



## Display UI Extension Potions（显示UI扩展点）

显示 UI 扩展点：Edit =》Editor Preferences =》General =》Miscellaneous =》勾选 Display UI Extension Points

![image-20240827152614370](.\img\image-20240827152614370.png)

如图， 我们想在编辑器中添加我们自己的UI项，可是，我们怎么知道应该挂载在哪里（或者说，怎么知道界面上的元素对应到代码里的挂载点是什么呢？）这个时候，UE编辑器设置里的Display UI Extension Potions（显示UI扩展点）就是做这个的



![image-20240827153039192](.\img\image-20240827153039192.png)

开启后重启编辑器，就可以看到UI扩展点了

![image-20240827153147400](.\img\image-20240827153147400.png)

```c++

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
```



自定义菜单项效果如下

![image-20240827155925993](.\img\image-20240827155925993.png)



# 搜索并删除未使用的资产

```C++
void FSuperManagerModule::OnDeleteUnusedAssetsButtonClicked()
{
	// 删除未使用的资产按钮点击事件
	if (SelectedFolderPaths.Num() > 1)
	{
		SM_Debug::ShowMessageDialog(FText::FromString("You can only select one folder at a time"), FText::FromString("Warning"), EAppMsgType::Ok);
		return;
	}

	const TArray<FString> AssetPathsName = UEditorAssetLibrary::ListAssets(SelectedFolderPaths[0], true);	// 获取文件夹下所有资产路径
	if (AssetPathsName.Num() == 0)
	{
		SM_Debug::ShowMessageDialog(FText::FromString("No assets found in the selected folder"), FText::FromString("Warning"), EAppMsgType::Ok);
		return;
	}

	EAppReturnType::Type Result = SM_Debug::ShowMessageDialog(FText::FromString("Are you sure you want to delete all unused assets in the selected folder?"), FText::FromString("Warning"), EAppMsgType::YesNo);

	if (Result == EAppReturnType::No)
	{
		return;
	}

	TArray<FAssetData> UnusedAssetsData;	// 未使用的资产数据
	for (const FString& AssetPath : AssetPathsName)
	{
		// 不要处理根路径下的 Developers 和 Collections 文件夹，因为这些文件夹通常是引擎或插件的文件夹，虽然不会出现在内容浏览器中，但是我们还是要做一下处理
		// 删除这两个文件夹下的内容会导致引擎或插件无法正常运行（崩溃）
		if (AssetPath.Contains(TEXT("Developers")) || AssetPath.Contains(TEXT("	Collections")))
		{
			continue;
		}

		if (!UEditorAssetLibrary::DoesAssetExist(AssetPath))
		{
			continue;
		}

		TArray<FString> AssetReferences = UEditorAssetLibrary::FindPackageReferencersForAsset(AssetPath);	// 获取资源引用者

		if (AssetReferences.Num() == 0)
		{
			const FAssetData AssetData = UEditorAssetLibrary::FindAssetData(AssetPath);	// 获取资产数据
			UnusedAssetsData.Add(AssetData);
		}
	}

	if (UnusedAssetsData.Num() > 0)
	{
		ObjectTools::DeleteAssets(UnusedAssetsData, true);	// 删除未使用的资产

		SM_Debug::ShowNotifyInfo(FText::FromString(FString::Printf(TEXT("Deleted %d unused assets"), UnusedAssetsData.Num())), FText::FromString("Success"));
	}
	else
	{
		SM_Debug::ShowMessageDialog(FText::FromString("No unused assets found in the selected folder"), FText::FromString("Warning"), EAppMsgType::Ok);
	}

}
```

