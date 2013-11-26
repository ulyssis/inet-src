#include "GrNeighborInfo.h"

bool equal(const GrNeighborInfo& a, const GrNeighborInfo& b)
{
	return a.getRouterAddress()==b.getRouterAddress()
		&& a.getRouterXPos()==b.getRouterXPos()
		&& a.getRouterYPos()==b.getRouterYPos();
}

