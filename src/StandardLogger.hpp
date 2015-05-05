#pragma once

#include <cstdio>
#include "ILogger.hpp"

namespace Logging
{
	namespace Loggers
	{
		class StandardLogger : public ILogger
		{
		protected:
			void onInfo(const std::string &msg) const;
			void onDebug(const std::string &msg) const;
			void onWarning(const std::string &msg) const;
			void onError(const std::string &msg) const;
			void onCritical(const std::string &msg) const;
		};
	}
}