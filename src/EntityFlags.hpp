#pragma once

#include <cstdint>

namespace EntityFlags
{
	enum EntityFlag : std::uint64_t
	{
		REMOVE		= 1,
		// rendering
		NODRAW		= 2,
		GLOW		= 4,
		BELOW		= 8,
		ABOVE		= 16,
		// collision
		COLLIDE		= 32,
        TRIGGER     = 64,
		// damage
		INVUNERABLE	= 128,
		HURTFUL 	= 256,
		// interactions
		PICKUP	    = 512
	};
}