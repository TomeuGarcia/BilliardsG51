#pragma once
#include <iostream>
#include <fstream>

#include "IBinarySerializable.h"
#include "../FilePathData.h"


class BinaryFile
{
public:
	BinaryFile(const std::string& path, const std::string& fileNameWithoutExtension);
	BinaryFile(const FilePathData& filePathData);

	void Write(IBinarySerializable* rootSerializable);
	void Read(IBinarySerializable* rootSerializable);


private:
	std::string m_completePathToFile;
};