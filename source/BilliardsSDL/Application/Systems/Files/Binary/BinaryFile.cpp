#include "BinaryFile.h"



BinaryFile::BinaryFile(const std::filesystem::path& path, const std::string& fileNameWithoutExtension)
	: m_completePathToFile(path / (fileNameWithoutExtension + ".bin"))
{
	if (!std::filesystem::exists(path))
	{
		std::filesystem::create_directory(path);
	}	
}

BinaryFile::BinaryFile(const FilePathData& filePathData)
	: BinaryFile(filePathData.p_path, filePathData.p_fileNameWithoutExtension)
{
}

void BinaryFile::Write(IBinarySerializable* rootSerializable)
{
	std::ofstream outputFile;
	outputFile.open(m_completePathToFile, std::ofstream::out | std::ifstream::binary);
	if (!outputFile.is_open())
	{
		//std::printf("Couldn't open file: %s\n", m_completePathToFile.c_str());
		return;
	}

	rootSerializable->WriteAsBinary(outputFile);

	outputFile.close();
}

void BinaryFile::Read(IBinarySerializable* rootSerializable)
{
	std::ifstream inputFile;
	inputFile.open(m_completePathToFile, std::ifstream::in | std::ifstream::binary);
	if (!inputFile.is_open())
	{
		//std::printf("Couldn't open file: %s\n", m_completePathToFile.c_str());
		return;
	}

	rootSerializable->ReadAsBinary(inputFile);

	inputFile.close();
}
