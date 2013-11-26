#include "BergerNeighborInfo.h"

bool equal(const BergerNeighborInfo& a, const BergerNeighborInfo& b)
{
	return a.getRouterAddress()==b.getRouterAddress()
		&& a.getRouterXPos()==b.getRouterXPos()
		&& a.getRouterYPos()==b.getRouterYPos()
		&& a.getGw1() == b.getGw1()
		&& a.getGw2() == b.getGw2();
}

