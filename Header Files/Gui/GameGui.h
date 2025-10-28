#pragma once

#include "IGui.h"

class GameGui : public IGui
{
public:
	GameGui() = default;

	void drawGui() override;
};
