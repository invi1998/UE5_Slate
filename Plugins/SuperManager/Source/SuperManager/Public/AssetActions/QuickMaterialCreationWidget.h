// Copyright INVI_1998

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "QuickMaterialCreationWidget.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMANAGER_API UQuickMaterialCreationWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
#pragma region QuickMaterialCreationCore
	UFUNCTION(BlueprintCallable, Category = "QuickMaterialCreationCore")
	void CreateMaterialFromSelectedTextures();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateMaterialFromSelectedTextures")
	FString MaterialName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CreateMaterialFromSelectedTextures")
	bool bUserSetMaterialName;		// 如果为true，则使用用户设置的材质名称，否则使用默认的材质名称

#pragma endregion

#pragma region SupportedTextureFormats
	// 基础颜色
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SupportedTextureFormats")
	TArray<FString> BaseColorArray = {
		"_BaseColor",
		"_Albedo",
		"_Diffuse",
		"_Color",
		"_Diff"
	};

	// 法线
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SupportedTextureFormats")
	TArray<FString> NormalArray = {
		"_Normal",
		"_Normals",
		"_Nrm",
		"_N",
		"_NrmMap",
		"_NormalMap"
	};

	// 粗糙度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SupportedTextureFormats")
	TArray<FString> RoughnessArray = {
		"_Roughness",
		"_Rough",
		"_RoughnessMap",
		"_RoughMap"
	};

	// 金属度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SupportedTextureFormats")
	TArray<FString> MetallicArray = {
		"_Metallic",
		"_Metal",
		"_MetallicMap",
		"_MetalMap"
	};

	// 环境光遮蔽
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SupportedTextureFormats")
	TArray<FString> AmbientOcclusionArray = {
		"_AO",
		"_AmbientOcclusion",
		"_Occlusion",
		"_AOMap",
		"_AmbientOcclusionMap"
	};

	// 高光
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SupportedTextureFormats")
	TArray<FString> SpecularArray = {
		"_Specular",
		"_Spec",
		"_SpecularMap",
		"_SpecMap"
	};

	// 切线
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SupportedTextureFormats")
	TArray<FString> TangentArray = {
		"_Tangent",
		"_TangentMap",
		"_TangentSpaceNormal"
	};

#pragma endregion


private:
#pragma region QuickMaterialCreation

	// 处理选中的数据
	bool ProcessSelectedData(const TArray<FAssetData>& SelectedAssetsData, TArray<UTexture2D*>& OutSelectedTexturesArray, FString& OutSelectedTexturePath);

	// 检查名称是否有效
	bool CheckIfNameIsValid(const FString& Name, const FString& FolderPath) const;

	// 创建材质
	UMaterial* CreateMaterial(const TArray<UTexture2D*>& TexturesArray, const FString& FolderPath) const;

	void Default_CreateMaterialNode(UMaterial* Material, UTexture2D* Texture, uint32& ConnectedPinsNum) const;

#pragma endregion

#pragma region CreateMaterialNode

	// 检查是否是支持的纹理格式
	bool TryConnectBaseColor(class UMaterialExpressionTextureSample* TextureSample, UTexture2D* Texture, UMaterial* Material) const;

#pragma endregion

};
