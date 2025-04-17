#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>

#include "IBinarySerializable.h"
#include "../FilePathData.h"


class BinaryFile
{
public:
	BinaryFile(const std::filesystem::path& path, const std::string& fileNameWithoutExtension);
	BinaryFile(const FilePathData& filePathData);

	void Write(IBinarySerializable* rootSerializable);
	void Read(IBinarySerializable* rootSerializable);


private:
	std::filesystem::path m_completePathToFile;
};