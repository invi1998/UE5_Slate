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

