#include "StandardLogger.hpp"

namespace Logging
{
	namespace Loggers
	{
		void StandardLogger::onInfo(const std::string &msg) const
		{
			std::printf("[INFO]\t%s\n", msg.c_str());
		}

		void StandardLogger::onDebug(const std::string &msg) const
		{
#ifdef _DEBUG
			std::printf("[DEBUG]\t%s\n", msg.c_str());
#endif
		}

		void StandardLogger::onWarning(const std::string &msg) const
		{
			std::printf("[WARNING]\t%s\n", msg.c_str());
		}

		void StandardLogger::onError(const std::string &msg) const
		{
			std::printf("[ERROR]\t%s\n", msg.c_str());
		}

		void StandardLogger::onCritical(const std::string &msg) const
		{
			std::printf("[CRITICAL]\t%s\n", msg.c_str());
		}
	}
}