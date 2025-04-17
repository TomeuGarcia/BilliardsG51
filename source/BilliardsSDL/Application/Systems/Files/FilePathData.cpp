#include "FilePathData.h"

FilePathData::FilePathData(const std::filesystem::path& path, const std::string& fileNameWithoutExtension)
	: p_path(path), p_fileNameWithoutExtension(fileNameWithoutExtension)
{
}
