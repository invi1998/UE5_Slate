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

void UQuickActorActionsWidget::DuplicateSelectedActors()
{
	if (!GetEditorActorSubsystem()) return;

	TArray<AActor*> SelectedActors = EditorActorSubsystem->GetSelectedLevelActors();		// 获取选中的Actor
	uint32 SelectedCount = 0;

	if (SelectedActors.Num() <= 0)
	{
		SM_Debug::ShowNotifyInfo(FText::FromString("No actor selected!"), FText::FromString("Warning"));
		return;
	}

	if (DuplicateCount <= 0)
	{
		SM_Debug::ShowNotifyInfo(FText::FromString("Duplicate count must be greater than 0!"), FText::FromString("Warning"));
		return;
	}

	if (DuplicateOffset == 0)
	{
		SM_Debug::ShowNotifyInfo(FText::FromString("Duplicate offset not equal 0!"), FText::FromString("Warning"));
		return;
	}

	for (AActor* Actor : SelectedActors)
	{
		if (Actor)
		{
			for (int i = 0; i < DuplicateCount; i++)
			{
				FVector Offset = FVector::ZeroVector;

				switch (DuplicateAxis)
				{
				case E_DuplicateAxis::EDA_XAxis:
					Offset.X = DuplicateOffset * (i + 1);
					break;
				case E_DuplicateAxis::EDA_YAxis:
					Offset.Y = DuplicateOffset * (i + 1);
					break;
				case E_DuplicateAxis::EDA_ZAxis:
					Offset.Z = DuplicateOffset * (i + 1);
					break;
				default:
					break;
				}

				if (AActor* NewActor = EditorActorSubsystem->DuplicateActor(Actor, Actor->GetWorld(), Offset))
				{
					EditorActorSubsystem->SetActorSelectionState(NewActor, true);	// 选中Actor
					SelectedCount++;
				}
			}
		}
	}

	if (SelectedCount > 0)
	{
		SM_Debug::ShowNotifyInfo(FText::FromString(FString::Printf(TEXT("Duplicated %d actors!"), SelectedCount)), FText::FromString("Success"));
	}
	else
	{
		SM_Debug::ShowNotifyInfo(FText::FromString("No actor duplicated!"), FText::FromString("Warning"));
	}
}

void UQuickActorActionsWidget::RandomizeSelectedActorsRotation()
{
	if (!GetEditorActorSubsystem()) return;

	TArray<AActor*> SelectedActors = EditorActorSubsystem->GetSelectedLevelActors();		// 获取选中的Actor
	uint32 SelectedCount = 0;

	if (SelectedActors.Num() <= 0)
	{
		SM_Debug::ShowNotifyInfo(FText::FromString("No actor selected!"), FText::FromString("Warning"));
		return;
	}

	for (AActor* Actor : SelectedActors)
	{
		if (Actor)
		{
			FRotator NewRotation = Actor->GetActorRotation();

			if (RandomRotation.bRandomPitch)
			{
				NewRotation.Pitch = FMath::RandRange(RandomRotation.MinPitch, RandomRotation.MaxPitch);
			}

			if (RandomRotation.bRandomYaw)
			{
				NewRotation.Yaw = FMath::RandRange(RandomRotation.MinYaw, RandomRotation.MaxYaw);
			}

			if (RandomRotation.bRandomRoll)
			{
				NewRotation.Roll = FMath::RandRange(RandomRotation.MinRoll, RandomRotation.MaxRoll);
			}

			Actor->SetActorRotation(NewRotation);
			SelectedCount++;
		}
	}

	if (SelectedCount > 0)
	{
		SM_Debug::ShowNotifyInfo(FText::FromString(FString::Printf(TEXT("Randomized %d actors rotation!"), SelectedCount)), FText::FromString("Success"));
	}
	else
	{
		SM_Debug::ShowNotifyInfo(FText::FromString("No actor randomized rotation!"), FText::FromString("Warning"));
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
