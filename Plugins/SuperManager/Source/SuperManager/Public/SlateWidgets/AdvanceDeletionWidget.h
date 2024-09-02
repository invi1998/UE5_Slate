// Copyright INVI_1998

#pragma once

#include "Widgets/SCompoundWidget.h"

class SAdvanceDeletionTab : public SCompoundWidget
{


	// SLATE_BEGIN_ARGS 是一个宏，用于定义构造函数的参数列表
	SLATE_BEGIN_ARGS(SAdvanceDeletionTab) {}

	SLATE_END_ARGS()

public:
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};

