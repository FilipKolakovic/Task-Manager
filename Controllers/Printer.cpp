#include "Printer.h"

#include<iostream>

Printer::Printer(const std::string& data)
	:buffer{ data }
{
}

void Printer::doAction()
{
	std::cout << buffer;
}
