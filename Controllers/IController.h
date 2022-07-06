#pragma once

// Interface for Controllers
class IController
{
public:
	virtual ~IController() = default;

	virtual void doAction() = 0;
};

