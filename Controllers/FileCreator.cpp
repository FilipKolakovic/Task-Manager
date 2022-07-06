#include "FileCreator.h"

#include <fstream>

FileCreator::FileCreator(const std::string& data, const std::string& fileName)
	: buffer {data }
	, mFileName{ fileName }
	, mFilePath{ mFileName + "_output.txt"}
{
}

void FileCreator::doAction()
{
	std::ofstream ofs(mFilePath.c_str(), std::ios_base::out | std::ios_base::app);
	ofs << mFileName;
	ofs.close();
}
