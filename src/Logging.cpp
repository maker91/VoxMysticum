#include "Logging.hpp"

namespace Logging
{
	std::shared_ptr<Loggers::ILogger> getLogger(const std::string &name)
	{
		return LOGGERS.at(name);
	}

	std::shared_ptr<Loggers::ILogger> Log = getLogger("console");
}