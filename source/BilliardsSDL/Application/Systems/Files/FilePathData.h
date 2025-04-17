#pragma once
#include <string>
#include <filesystem>


struct FilePathData
{
public:
	FilePathData(const std::filesystem::path& path, const std::string& fileNameWithoutExtension);

public:
	std::filesystem::path p_path;
	std::string p_fileNameWithoutExtension;
};