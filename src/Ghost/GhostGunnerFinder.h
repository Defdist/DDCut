#pragma once

#include "GhostGunner.h"

#include <list>
#include <string>

class GhostGunnerFinder
{
public:
	std::list<GhostGunner> GetAvailableGhostGunners() const;
};
