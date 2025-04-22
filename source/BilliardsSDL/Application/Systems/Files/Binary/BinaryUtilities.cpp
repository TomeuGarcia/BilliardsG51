#include "BinaryUtilities.h"



void BinaryUtilities::ReadInt(std::ifstream& inputStream, int& intValue)
{
	inputStream.read(reinterpret_cast<char*>(&intValue), sizeof(int));
}

void BinaryUtilities::WriteInt(std::ofstream& outputStream, int& intValue)
{
	outputStream.write(reinterpret_cast<char*>(&intValue), sizeof(int));
}



void BinaryUtilities::ReadString(std::ifstream& inputStream, std::string& stringValue)
{
	size_t stringSize;
	inputStream.read(reinterpret_cast<char*>(&stringSize), sizeof(size_t));

	stringValue.resize(stringSize);

	inputStream.read(reinterpret_cast<char*>(stringValue.data()), stringSize);
}


void BinaryUtilities::WriteString(std::ofstream& outputStream, const std::string& stringValue)
{
	size_t stringSize = stringValue.size();
	outputStream.write(reinterpret_cast<char*>(&stringSize), sizeof(size_t));
	outputStream.write(stringValue.c_str(), stringSize);
}
