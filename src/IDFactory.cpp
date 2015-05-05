#include "IDFactory.hpp"

uid IDFactory::generate(const std::string &what)
{
	if (!ids.count(what))
		ids[what] = 0;
	return ids[what]++;
}

std::map<std::string, uid> IDFactory::ids;