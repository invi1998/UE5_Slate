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



