#pragma once
#include <fstream>
#include "BinaryUtilities.h"


class IBinarySerializable
{
public:
	virtual void ReadAsBinary(std::ifstream& inputStream) = 0;
	virtual void WriteAsBinary(std::ofstream& outputStream) = 0;
};