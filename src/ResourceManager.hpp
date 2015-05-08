#pragma once

#include <map>
#include <memory>
#include <string>

#include "Resources/IBaseResource.hpp"
#include "Logging.hpp"

class ResourceManager
{
public:
	template <typename T, typename... Args>
	static std::shared_ptr<T> get(const std::string &name, Args... args)
	{
		std::shared_ptr<T> resource;
		if (resources.count(name))
		{
			resource = std::dynamic_pointer_cast<T>(resources[name]);
		}
		else 
		{
			Logging::Log->info("Loading resource: " + name);
			resource = std::make_shared<T>(args...);
			if (!resource->load(name))
			{
				Logging::Log->error("Failed to load resource: " + name);
				resource->fallback();
			}
			resources[name] = resource;
		}
		return resource;
	};

private:
	static std::map<std::string, std::shared_ptr<IBaseResource>> resources;
};
