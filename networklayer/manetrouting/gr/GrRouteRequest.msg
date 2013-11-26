// Di: new class GrRouteRequest extends the class IPv4Address and Coord.

cplusplus {{
#include "IPv4Address.h"
#include "Coord.h"
}}

class noncobject IPv4Address;
class noncobject Coord;

packet GrRouteRequest
{
	IPv4Address src;
	IPv4Address dst;
	Coord srcPos;
	Coord dstPos;
}

