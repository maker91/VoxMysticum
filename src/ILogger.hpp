#pragma once

#include <string>
#include <cstdio>

/*
Standard interface for logging
*/
namespace Logging
{
	namespace Loggers
	{
		class ILogger
		{
		public:
			template <typename... Args>
			void info(const std::string &fmt, Args... args)
			{
				char buf[1024];
				sprintf_s(buf, fmt.c_str(), args...);
				onInfo(buf);
			}

			template <typename... Args>
			void debug(const std::string &fmt, Args... args)
			{
				char buf[1024];
				sprintf_s(buf, fmt.c_str(), args...);
				onDebug(buf);
			}

			template <typename... Args>
			void warning(const std::string &fmt, Args... args)
			{
				char buf[1024];
				sprintf_s(buf, fmt.c_str(), args...);
				onWarning(buf);
			}

			template <typename... Args>
			void error(const std::string &fmt, Args... args)
			{
				char buf[1024];
				sprintf_s(buf, fmt.c_str(), args...);
				onError(buf);
			}

			template <typename... Args>
			void critical(const std::string &fmt, Args... args)
			{
				char buf[1024];
				sprintf_s(buf, fmt.c_str(), args...);
				onCritical(buf);
			}

		protected:
			virtual void onInfo(const std::string &) const = 0;
			virtual void onDebug(const std::string &) const = 0;
			virtual void onWarning(const std::string &) const = 0;
			virtual void onError(const std::string &) const = 0;
			virtual void onCritical(const std::string &) const = 0;
		};
	}
}