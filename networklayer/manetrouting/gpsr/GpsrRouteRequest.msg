// Di: new class GpsrRouteRequest extends the class IPv4Address and Coord.

cplusplus {{
#include "IPv4Address.h"
#include "Coord.h"
}}

class noncobject IPv4Address;
class noncobject Coord;

packet GpsrRouteRequest
{
	IPv4Address src;
	IPv4Address dst;
	Coord srcPos;
	Coord dstPos;
}

