// Copyright INVI_1998

#pragma once

#include "Framework/Commands/Commands.h"

// UI
class FSuperManagerUICommands : public TCommands<FSuperManagerUICommands>
{
	public:

	FSuperManagerUICommands()
		: TCommands<FSuperManagerUICommands>(
			"SuperManager",
			NSLOCTEXT("Contexts", "SuperManagerUICommands", "SuperManagerUICommands"),
			NAME_None,
			"SuperManager") {}

	// TCommand<> interface
	virtual void RegisterCommands() override;
};
