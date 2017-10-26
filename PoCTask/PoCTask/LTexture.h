#pragma once

#include <string.h>

using namespace std;

class LTexture
{
public:
	LTexture();
	~LTexture();
	bool loadFromFile(string path);
};

