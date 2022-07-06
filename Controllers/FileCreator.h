#pragma once

#include "IController.h"
#include <string>

// Controller FileCreator - create new text file and write data there

class FileCreator : public IController
{
public:
	FileCreator() = delete;
	FileCreator(const std::string& data, const std::string& fileName);
	~FileCreator() override = default;

	void doAction() override;
private:
	std::string buffer;
	std::string mFileName;
	std::string mFilePath;
};

