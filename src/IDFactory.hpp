#pragma once

#include <map>
#include <string>
#include <cstdint>

using uid = std::uint32_t;

class IDFactory
{
public:
	static uid generate(const std::string &what);

private:
	static std::map<std::string, uid> ids;
};