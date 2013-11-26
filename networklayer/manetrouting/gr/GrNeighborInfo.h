#pragma once

#define BNI_INCLUDESAFE

#include "GrNeighborInfo_m.h"

bool equal(const GrNeighborInfo& a, const GrNeighborInfo& b);

struct hashIPv4Address
    {
	size_t operator()(const IPv4Address& x) const
	    {
		return x.getInt();
	    }
    };

