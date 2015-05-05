#pragma once

#include <map>
#include <string>
#include <memory>
#include "ILogger.hpp"

#include "StandardLogger.hpp"

namespace Logging
{
	static const std::map<std::string, std::shared_ptr<Loggers::ILogger>> LOGGERS = {
		{ "console", std::make_shared<Loggers::StandardLogger>() },
	};

	std::shared_ptr<Loggers::ILogger> getLogger(const std::string &name);

	// Quick access to the main logger (console for now)
	extern std::shared_ptr<Loggers::ILogger> Log;
}