#pragma once
#include <string>

struct FilePathData
{
public:
	FilePathData(const std::string& path, const std::string& fileNameWithoutExtension);

public:
	std::string p_path;
	std::string p_fileNameWithoutExtension;
};