#pragma once

#include <string>

class IBaseResource
{
public:
	virtual bool load(const std::string &) = 0;
	virtual void fallback() {};
};