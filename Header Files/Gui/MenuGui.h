#pragma once

#include "IGui.h"

class MenuGui : public IGui
{
public:
	MenuGui() = default;

	void drawGui() override;
};
