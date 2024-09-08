// Copyright INVI_1998


#include "ActorAction/QuickActorActionsWidget.h"
#include "Subsystems/EditorActorSubsystem.h"
#include "DebugHeader.h"

void UQuickActorActionsWidget::SelectAllActorsWithSimilarName()
{
	if (!GetEditorActorSubsystem()) return;

	TArray<AActor*> SelectedActors = EditorActorSubsystem->GetSelectedLevelActors();		// 获取选中的Actor
	uint32 SelectedCount = 0;

	if (SelectedActors.Num() <= 0)
	{
		SM_Debug::ShowNotifyInfo(FText::FromString("No actor selected!"), FText::FromString("Warning"));
		return;
	}

	if (SelectedActors.Num() > 1)
	{
		SM_Debug::ShowNotifyInfo(FText::FromString("Only one actor can be selected!"), FText::FromString("Warning"));
		return;
	}

	const FString ActorName = SelectedActors[0]->GetActorLabel();		// 获取选中的Actor的名称
	const FString NameToSearch = ActorName.LeftChop(4);			// 去掉最后四位字符

	TArray<AActor*> AllActors = EditorActorSubsystem->GetAllLevelActors();	// 获取所有的Actor

	for (AActor* Actor : AllActors)
	{
		if (Actor && Actor->GetActorLabel().Contains(NameToSearch))
		{
			EditorActorSubsystem->SetActorSelectionState(Actor, true);	// 选中Actor
			SelectedCount++;
		}
	}

	if (SelectedCount > 0)
	{
		SM_Debug::ShowNotifyInfo(FText::FromString(FString::Printf(TEXT("Selected %d actors!"), SelectedCount)), FText::FromString("Success"));
	}
	else
	{
		SM_Debug::ShowNotifyInfo(FText::FromString("No actor selected!"), FText::FromString("Warning"));
	}

}

bool UQuickActorActionsWidget::GetEditorActorSubsystem()
{
	if (EditorActorSubsystem == nullptr)
	{
		EditorActorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
	}

	return EditorActorSubsystem != nullptr;
}
