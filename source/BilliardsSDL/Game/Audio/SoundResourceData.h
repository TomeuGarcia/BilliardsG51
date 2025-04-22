#pragma once
#include <string>


struct SoundResourceData
{
public:
	SoundResourceData(const std::string& sourcePath);

public:
	std::string p_sourcePath;
};