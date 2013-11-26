#pragma once

#define BNI_INCLUDESAFE

#include "GpsrNeighborInfo_m.h"

bool equal(const GpsrNeighborInfo& a, const GpsrNeighborInfo& b);

struct hashIPv4Address
{
	size_t operator()(const IPv4Address& x) const
	{
		return x.getInt();
	}
};

