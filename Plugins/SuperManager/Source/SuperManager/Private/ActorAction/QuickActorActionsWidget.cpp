// Copyright INVI_1998


#include "ActorAction/QuickActorActionsWidget.h"
#include "Subsystems/EditorActorSubsystem.h"

bool UQuickActorActionsWidget::GetEditorActorSubsystem()
{
	if (EditorActorSubsystem == nullptr)
	{
		EditorActorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
	}

	return EditorActorSubsystem != nullptr;
}
