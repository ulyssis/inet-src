cplusplus {{
#include "IPv4Address.h"
}}

class noncobject IPv4Address;

packet BergerNeighborInfo
{
	IPv4Address routerAddress;
	double routerXPos;
	double routerYPos;
	IPv4Address gw1;
    IPv4Address gw2;
}

