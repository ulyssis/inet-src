// Di: new class GpsrRouteRequest extends the class IPv4Address and Coord.

cplusplus {{
#include "IPv4Address.h"
#include "Coord.h"
#include <list>
typedef std::list<int> PassedNode;
}}

class noncobject IPv4Address;
class noncobject Coord;
class noncobject PassedNode;

packet GpsrRouteRequest
{
    PassedNode passedNode;
	IPv4Address src;
	IPv4Address dst;
	Coord srcPos;
	Coord dstPos;
	
}

