#pragma once

#include <map>
#include <string>
#include "json/json.h"

class Config : public Json::Value
{
public:
	Config(Config &) = delete;
	void operator=(Config &) = delete;

	void saveToFile(std::string filename);
	bool loadFromFile(std::string filename);

	static Config config;

private:
	Config() {};
};