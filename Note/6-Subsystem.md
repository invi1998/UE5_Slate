# 编程子系统

[编程子系统 | 虚幻引擎 4.27 文档 | Epic Developer Community (epicgames.com)](https://dev.epicgames.com/documentation/zh-cn/unreal-engine/programming-subsystems?application_version=4.27)

虚幻引擎4（UE4）中的子系统是生命周期受控的自动实例化类。这些类提供了易用的扩展点，程序员可直接获得蓝图和Python公开，同时避免繁复的引擎类修改或覆盖。

当前支持的子系统生命周期包括：

| 子系统       | 继承自                      |
| ------------ | --------------------------- |
| **引擎**     | `UEngineSubsystem` 类       |
| **编辑器**   | `UEditorSubsystem` 类       |
| **游戏实例** | `UGameInstanceSubsystem` 类 |
| **本地玩家** | `ULocalPlayerSubsystem` 类  |

举例而言，如果创建了一个派生自此基类的类：

```cpp
	class UMyGamesSubsystem : public UGameInstanceSubsystem
```

将出现以下结果：

1. 创建 `UGameInstance` 之后，还会创建一个名为 `UMyGamesSubsystem` 的实例。
2. `UGameInstance` 初始化时，将在子系统上调用 `Initialize()`。
3. `UGameInstance` 关闭时，将在子系统上调用 `Deinitialize()`。
4. 此时将放弃对子系统的引用，如果不再有对子系统的引用，则其将被垃圾回收。

## 使用子系统的原因

使用编程子系统有以下几个原因：

- 子系统可节省编程时间。
- 子系统使您无需覆盖引擎类。
- 子系统使您无需再已经很复杂的类上添加更多API。
- 子系统使您能通过用户友好的类型化节点来访问蓝图。
- 子系统允许访问Python脚本来编写编辑器脚本或编写测试代码。
- 子系统在代码库中提供模块化和一致性。

子系统在创建插件时尤为实用。您不需要代码相关的说明即可让插件工作。用户只需将插件添加到游戏中，就可以确切了解插件将在何时被实例化和初始化。因此，您可以专注于UE4中提供的API和功能的使用方式。

## 用蓝图访问子系统

子系统将自动公开到蓝图，智能节点理解情境，且不需要强制转换。您可以使用标准的 `UFUNCTION()` 标记和规则来控制蓝图可以使用哪些API。

右键点击蓝图图表来显示快捷菜单并搜索“子系统”，将出现类似于下图的内容。这里有每个主要类型的类目，以及每个特定子系统的单个条目。 ![img](https://d1iv7db44yhgxn.cloudfront.net/documentation/images/6967f786-b005-449a-92c0-4eef3f04ba36/subsystems_01.png)

如果从上添加节点，将得到如下结果。 ![img](https://d1iv7db44yhgxn.cloudfront.net/documentation/images/bd4f0f49-3943-49cc-8f2a-1bf96c61a218/subsystems_02.png)

## 用Python访问子系统

如果正在使用Python，则可以用内置访问器来访问子系统，如下方示例所示。

```cpp
	my_engine_subsystem = unreal.get_engine_subsystem(unreal.MyEngineSubsystem)
	my_editor_subsystem = unreal.get_editor_subsystem(unreal.MyEditorSubsystem)
```



Python当前是一个实验性功能。

## 子系统生命周期细节

### 引擎子系统

```cpp
	class UMyEngineSubsystem : public UEngineSubsystem { ... };
```

当引擎子系统的模块加载时，子系统将在模块的 `Startup()` 函数返回后执行 `Initialize()`，子系统将在模块的 `Shutdown()` 函数返回后执行 `Deinitialize()`。

这些子系统通过GEngine访问，如下所示。

```cpp
	UMyEngineSubsystem* MySubsystem = GEngine->GetEngineSubsystem<UMyEngineSubsystem>();
```

### 编辑器子系统

```cpp
	class UMyEditorSubsystem : public UEditorSubsystem { ... };
```

当编辑器子系统的模块加载时，子系统将在模块的 `Startup()` 函数返回后执行 `Initialize()`，子系统将在模块的 `Shutdown()` 函数返回后执行 `Deinitialize()`。

这些子系统可通过GEEditor访问，如下所示。

```cpp
	UMyEditorSubsystem* MySubsystem = GEditor->GetEditorSubsystem<UMyEditorSubsystem>();
```

### GameInstance子系统

```cpp
	class UMyGameSubsystem : public UGameInstanceSubsystem { ... };
```

这些子系统可通过UGameInstance访问，如下所示。

```cpp
	UGameInstance* GameInstance = ...;
	UMyGameSubsystem* MySubsystem = GameInstance->GetSubsystem<UMyGameSubsystem>();
```

### LocalPlayer子系统

```cpp
	class UMyPlayerSubsystem : public ULocalPlayerSubsystem { ... };
```

这些子系统可通过ULocalPlayer访问，如下所示。

```cpp
	ULocalPlayer* LocalPlayer = ...;
	UMyPlayerSubsystem * MySubsystem = LocalPlayer->GetSubsystem<UMyPlayerSubsystem>();
```

## 子系统范例

在以下示例中，我们希望为游戏添加一个统计数据系统，以跟踪收集资源的数量。

我们可以从 `UGameInstance` 派生，并创建 `UMyGamesGameInstance`，然后为其添加 `IncrementResourceStat()` 函数。然而我们知道，团队最终希望添加其他统计数据以及统计数据聚合器和统计数据的保存/加载等。因此，您决定将所有这些内容放入类中，例如 `UMyGamesStatsSubsystem`。

同样，我们可以创建 `UMyGamesGameInstance` 并添加 `UMyGamesStatsSubsystem` 类型的成员。然后我们可以向它添加一个存取器，并连接Initialize和Deinitialize函数。然而这会存在几个问题。

- 不存在 `UGameInstance` 的游戏特定导数。
- `UMyGamesGameInstance` 存在，但是它已拥有大量函数，添加更多函数并不理想。

在一个足够复杂的游戏中，从 `UGameInstance` 进行派生有很多好处。然而当您拥有子系统时，便不需要使用它。最重要的是，较之于使用其他方法，使用子系统需要编写的代码更少。

因此，我们最终使用的代码将显示在下例中。

```cpp
	UCLASS()
	class UMyGamesStatsSubsystem : public UGameInstanceSubsystem
	{
		GENERATED_BODY()
	public:
		// Begin USubsystem
		virtual void Initialize(FSubsystemCollectionBase& Collection) override;
		virtual void Deinitialize() override;
		// End USubsystem
 
		void IncrementResourceStat();
	private:
		// All my variables
	};
```



# UEditorActorSubsystem

在Unreal Engine 5 (UE5) 中，`UEditorActorSubsystem` 是一个特殊的子系统，主要用于处理编辑器环境中的Actor操作。这个子系统特别设计用于支持编辑器中的各种功能，比如选择、放置、移动和删除Actor等。它不是在游戏运行时使用的子系统，而是专门为编辑器环境设计的，以帮助开发者在编辑器中更好地管理和操作场景中的Actor。

### 功能

`UEditorActorSubsystem` 主要提供了以下功能：

1. **Actor管理**：管理编辑器中所有Actor的状态，包括选择状态、可见性、锁定状态等。
2. **操作工具集成**：与编辑器中的各种工具（如选择工具、移动工具、旋转工具等）集成，使得这些工具能够有效地操作Actor。
3. **场景操作**：支持场景中的Actor操作，如复制、粘贴、删除等。
4. **预览Actor管理**：处理编辑器中预览Actor的创建和销毁，这些Actor通常用于预览某些效果或模板。
5. **脚本化编辑器操作**：支持通过脚本或程序化的方式执行编辑器操作，方便自动化测试或批量修改。

### 应用场景

`UEditorActorSubsystem` 的主要应用场景是在编辑器环境中，特别是在以下情况下：

- 当开发者需要在编辑器中创建复杂的场景时，该子系统可以帮助管理大量的Actor。
- 在编辑器中进行自动化测试时，可以利用这个子系统来模拟用户操作，比如移动或旋转Actor。
- 在脚本化编辑工作流程中，该子系统提供了API来实现对编辑器内Actor的操作。



# ISceneOutlinerInterface

`ISceneOutlinerInterface` 是在 Unreal Engine (UE) 中的一个接口，它主要用于处理场景大纲视图（Scene Outliner）的交互。场景大纲视图是UE编辑器中的一个功能，允许用户以层次结构的形式查看场景中的所有Actor（可视为3D场景中的对象或实体）。这使得用户可以更容易地管理和操作场景中的大量Actor。

在UE中，尤其是从UE4开始，场景大纲视图就作为视口的一部分存在，并且在UE5中得到了进一步的发展。通过实现 `ISceneOutlinerInterface` 接口，开发人员可以使他们的自定义Actor类型更好地集成到场景大纲视图的功能中，比如添加自定义列、过滤器或者上下文菜单项等。
