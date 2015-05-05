#include <fstream>

#include "Config.hpp"
#include "Logging.hpp"

void Config::saveToFile(std::string filename)
{
	Logging::Log->info("Saving config file: %s", filename.c_str());

	std::ofstream file(("Data/Config/" + filename).c_str());
	Json::StyledStreamWriter writer;
	writer.write(file, *this);
}

bool Config::loadFromFile(std::string filename)
{
	Logging::Log->info("Loading config file: %s", filename.c_str());

	std::ifstream file(("Data/Config/" + filename).c_str());
	if (!file.is_open())
	{
		Logging::Log->error("Can't open Config file: %s", filename.c_str());
		return false;
	}
	std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));

	Json::Reader reader;
	if (!reader.parse(content, *this))
	{
		Logging::Log->error("Failed to parse Config file: %s\n%s", filename.c_str(), reader.getFormattedErrorMessages().c_str());
		return false;
	}

	return true;
}

Config Config::config;