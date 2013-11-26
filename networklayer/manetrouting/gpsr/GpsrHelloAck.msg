cplusplus {{
#include "IPv4Address.h"
#include "Coord.h"
}}

class noncobject IPv4Address;
class noncobject Coord;

packet GpsrHelloAck
{
	IPv4Address myAddress;
	IPv4Address DstAddress;
	Coord MyPos;
}

