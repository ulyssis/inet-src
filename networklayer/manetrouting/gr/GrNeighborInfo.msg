cplusplus {{
#include "IPv4Address.h"
}}

class noncobject IPv4Address;

packet GrNeighborInfo
{
	IPv4Address routerAddress;
	double routerXPos;
	double routerYPos;
}

