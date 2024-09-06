// Copyright INVI_1998


#include "AssetActions/QuickMaterialCreationWidget.h"
#include "DebugHeader.h"
#include "EditorAssetLibrary.h"
#include "EditorUtilityLibrary.h"
#include "AssetToolsModule.h"
#include "Factories/MaterialFactoryNew.h"
#include "Materials/MaterialExpressionTextureSample.h"

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

	if (!CheckIfNameIsValid(MaterialName, SelectedTextureFolderPath))
	{
		SelectedTexturesArray.Empty();
		SelectedTextureFolderPath.Empty();
		return;
	}

	if (UMaterial* NewMaterial = CreateMaterial(SelectedTexturesArray, SelectedTextureFolderPath))
	{
		uint32 ConnectedPinsNum = 0;
		// 遍历纹理，给材质设置参数
		for (UTexture2D* Texture : SelectedTexturesArray)
		{
			if (!Texture)
			{
				continue;
			}

			Default_CreateMaterialNode(NewMaterial, Texture, ConnectedPinsNum);
		}
	}


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
				SM_Debug::ShowMessageDialog(FText::FromString( AssetData.AssetName.ToString() + " is not a valid Texture!"), FText::FromString("Error"), EAppMsgType::Ok);
				return false;
			}
		}
		else
		{
			SM_Debug::ShowMessageDialog(FText::FromString("Selected Asset: " + AssetData.AssetName.ToString() + " is not a Texture!"), FText::FromString("Error"), EAppMsgType::Ok);
			return false;
		
		}
	}

	return true;

}

bool UQuickMaterialCreationWidget::CheckIfNameIsValid(const FString& Name, const FString& FolderPath) const
{
	// 检查当前目录下是否有同名的材质
	TArray<FString> ExistingAssetsPaths = UEditorAssetLibrary::ListAssets(FolderPath, false);

	for (const FString& AssetPath : ExistingAssetsPaths)
	{
		const FString ExistingAssetName = FPaths::GetBaseFilename(AssetPath);

		if (ExistingAssetName == Name)
		{
			SM_Debug::ShowMessageDialog(FText::FromString("Material Name: \" " + Name + " \" is already exist!"), FText::FromString("Error"), EAppMsgType::Ok);
			return false;
		}
	}

	return true;
}

UMaterial* UQuickMaterialCreationWidget::CreateMaterial( const TArray<UTexture2D*>& TexturesArray, const FString& FolderPath) const
{
	UMaterial* NewMaterial = nullptr;

	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");

	UMaterialFactoryNew* MaterialFactory = NewObject<UMaterialFactoryNew>();

	UObject* NewObject = AssetToolsModule.Get().CreateAsset(MaterialName, FolderPath, UMaterial::StaticClass(), MaterialFactory);

	if (NewObject)
	{
		NewMaterial = Cast<UMaterial>(NewObject);

		if (NewMaterial)
		{
			// 设置材质参数
			NewMaterial->SetTextureParameterValueEditorOnly(FName("Texture"), TexturesArray[0]);
		}
	}

	return NewMaterial;
}

void UQuickMaterialCreationWidget::Default_CreateMaterialNode(UMaterial* Material, UTexture2D* Texture, uint32& ConnectedPinsNum) const
{
	UMaterialExpressionTextureSample* TextureSample = NewObject<UMaterialExpressionTextureSample>(Material);

	if (TextureSample)
	{
		if (TryConnectBaseColor(TextureSample, Texture, Material))
		{
			ConnectedPinsNum++;
		}
	}
}

bool UQuickMaterialCreationWidget::TryConnectBaseColor(UMaterialExpressionTextureSample* TextureSample, UTexture2D* Texture, UMaterial* Material) const
{
	for (const FString& BaseColor : BaseColorArray)
	{
		if (Texture->GetName().Contains(BaseColor))
		{
			TextureSample->Texture = Texture;

			Material->GetExpressionCollection().AddExpression(TextureSample);
			Material->GetExpressionInputForProperty(MP_BaseColor)->Connect(0, TextureSample);
			Material->PostEditChange();

			TextureSample->MaterialExpressionEditorX -= 600;

			return true;
		}
	}

	return false;
}

#pragma endregion

