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

};
