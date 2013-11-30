cplusplus {{
#include "IPv4Address.h"
#include "Coord.h"
#include <list>
typedef std::list<int> Route;
}}

class noncobject IPv4Address;
class noncobject Coord;
class noncobject Route;

packet BergerTestPkt
{
    Route route;
	int hops;
	IPv4Address nextHop;
	IPv4Address dst;
}
