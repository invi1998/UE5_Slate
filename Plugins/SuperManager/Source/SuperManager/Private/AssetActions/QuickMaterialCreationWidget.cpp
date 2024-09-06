// Copyright INVI_1998


#include "AssetActions/QuickMaterialCreationWidget.h"
#include "DebugHeader.h"
#include "EditorUtilityLibrary.h"

#pragma region QuickMaterialCreationCore

void UQuickMaterialCreationWidget::CreateMaterialFromSelectedTextures()
{
	if (bUserSetMaterialName)
	{
		if (MaterialName.IsEmpty())
		{
			SM_Debug::ShowMessageDialog(FText::FromString("Material Name is Empty!"), FText::FromString("Error"), EAppMsgType::Ok);
			return;
		}
	}
	else
	{
		MaterialName = "M_NewMaterial";
	}

	const TArray<FAssetData> SelectedAssetsData = UEditorUtilityLibrary::GetSelectedAssetData();
	TArray<UTexture2D*> SelectedTexturesArray;
	FString SelectedTextureFolderPath;

	if (!ProcessSelectedData(SelectedAssetsData, SelectedTexturesArray, SelectedTextureFolderPath))
	{
		SelectedTexturesArray.Empty();
		SelectedTextureFolderPath.Empty();
		return;
	}

	SM_Debug::PrintDebug(FString::Printf(TEXT("Selected Texture Path: %s"), *SelectedTextureFolderPath), FColor::Green);

}



#pragma endregion

#pragma region QuickMaterialCreation

bool UQuickMaterialCreationWidget::ProcessSelectedData(const TArray<FAssetData>& SelectedAssetsData, TArray<UTexture2D*>& OutSelectedTexturesArray, FString& OutSelectedTexturePath)
{
	if (SelectedAssetsData.Num() == 0)
	{
		SM_Debug::ShowMessageDialog(FText::FromString("No Texture Selected!"), FText::FromString("Error"), EAppMsgType::Ok);
		return false;
	}

	bool bSetMaterialName = false;
	for (const FAssetData& AssetData : SelectedAssetsData)
	{
		if (AssetData.AssetClassPath == UTexture2D::StaticClass()->GetClassPathName())
		{
			if (UTexture2D* Texture = Cast<UTexture2D>(AssetData.GetAsset()))
			{
				OutSelectedTexturesArray.Add(Texture);

				if (OutSelectedTexturePath.IsEmpty())
				{
					OutSelectedTexturePath = AssetData.PackagePath.ToString();
				}

				if (!bUserSetMaterialName && !bSetMaterialName)
				{
					MaterialName = Texture->GetName();
					MaterialName.RemoveFromStart("T_");
					MaterialName.RemoveFromStart("t_");

					MaterialName = "M_" + MaterialName;

					bSetMaterialName = true;
				}
				
			}
			else
			{
				SM_Debug::ShowMessageDialog(FText::FromString("Selected Asset is not a Texture!"), FText::FromString("Error"), EAppMsgType::Ok);
				return false;
			}
		}
	}

	return true;

}

#pragma endregion

