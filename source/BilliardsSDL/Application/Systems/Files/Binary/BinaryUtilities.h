#pragma once
#include <fstream>


namespace BinaryUtilities
{
	void ReadInt(std::ifstream& inputStream, int& intValue);
	void WriteInt(std::ofstream& outputStream, int& intValue);

	void ReadString(std::ifstream& inputStream, std::string& stringValue);
	void WriteString(std::ofstream& outputStream, const std::string& stringValue);
}