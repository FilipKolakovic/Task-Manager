#pragma once

#include "IController.h"
#include <string>

// Controller Printer - print data to the consol output

class Printer : public IController
{
public:
	Printer() = delete;
	Printer(const std::string& data);
	~Printer() override = default;

	void doAction() override;
private:
	std::string buffer;
};

