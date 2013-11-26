#include "GpsrNeighborInfo.h"

bool equal(const GpsrNeighborInfo& a, const GpsrNeighborInfo& b)
{
	return a.getRouterAddress()==b.getRouterAddress()
		&& a.getRouterXPos()==b.getRouterXPos()
		&& a.getRouterYPos()==b.getRouterYPos();
}

