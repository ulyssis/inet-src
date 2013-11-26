// System includes:

// Omnet includes:

// INET includes:
#include "Coord.h"
#include "IMobility.h"
#include "IPv4Datagram.h"
#include "IPv4ControlInfo.h"
#include "ControlManetRouting_m.h"

// GR includes:
#include "gr.h"

Define_Module(GR);

GR::posTable_t GR::posTable;

void GR::initialize(int stage)
{
	if(stage==4)
	    {
	    registerRoutingModule();
		registerPosition(); // We register for position information, but unfortunately we will not get up-to-date information before the first update :( // Di:?? )

		// Determine position and IP:
		routingTable=check_and_cast<IRoutingTable*>(getParentModule()->getSubmodule("routingTable"));
		myAddr=routingTable->getRouterId();
		ev << "GR: My (" << myAddr << ") position: (" << getXPos() << "," << getYPos() << ")" << endl;
		// Broadcast position information to neighbors:
		GrNeighborInfo* bni=new GrNeighborInfo();
		bni->setRouterAddress(myAddr);
		bni->setRouterXPos(getXPos()); //record the current position
		bni->setRouterYPos(getYPos());
		doLocalBroadcast(bni);
        cMessage *beaconing = new cMessage("beaconing");
        scheduleAt(0.85, beaconing);
	    }
}

void GR::doLocalBroadcast(cPacket *pk)
    {
	IPv4Datagram* p=new IPv4Datagram();
	p->setSrcAddress(myAddr);
	p->setDestAddress(IPv4Address::ALLONES_ADDRESS); // Di: broadcast to all?
	p->setTimeToLive(1);
	p->setTransportProtocol(IP_PROT_MANET);
	IPv4ControlInfo *ipControlInfo = new IPv4ControlInfo();
	ipControlInfo->setProtocol(IP_PROT_MANET);
	ipControlInfo->setSrcAddr(myAddr);
	ipControlInfo->setDestAddr(IPv4Address::ALLONES_ADDRESS);
	ipControlInfo->setTimeToLive(1);
	p->setControlInfo(ipControlInfo);
	p->encapsulate(pk); //pk, here is of GrNeighborInfo, is encapsulated in a IPv4Datagram pointed by 'p'.
	float delay=exponential(10e-3);
	sendDelayed(p,delay,"to_ip"); //message 'p' is broadcasted, which contains the IP address of the sender, low tx power.
    }

void GR::handleMessage(cMessage *msg) //class SIM_API cPacket : public cMessage
{
	if(GrNeighborInfo* bni=dynamic_cast<GrNeighborInfo*>(msg))
	    {
		const IPv4Address neighborAddr=bni->getRouterAddress();
		//printf("GR: %s received message (%s,%f,%f)\n", myAddr.str().c_str(), neighborAddr.str().c_str(), bni->getRouterXPos(), bni->getRouterYPos());

		// from myself
		if(neighborAddr == myAddr)
		    {
			ev << "GR: Discarding neighbor info from myself" << endl;
			delete bni;
			return;
		    }

        /*
         * restore received neighbor information which will be cleared every beaconing interval
         */
        if(neighborAddr!=myAddr)
            {
            neighborhoodBackup[neighborAddr]=bni;
            return;
            }

		nh_t::const_iterator it=neighborhood.find(neighborAddr);//      typedef std::tr1::unordered_map<IPv4Address,GrNeighborInfo*,hashIPv4Address> nh_t;

		// Entry exists (the first condition below shows that the iterator (it) doesn't point to map::end), no update:
		if(it!=neighborhood.end() && equal(*(*it).second,*bni))
		    {
			ev << "GR: Entry already exists, discarding" << endl;
			delete bni;
			return;
		    }

		// Entry exists, update (the new position)
		if(it!=neighborhood.end())
		    {
			// delete old entry:
			delete (*it).second;
			// insert new entry:
			neighborhood[neighborAddr]=bni;
			// update local links:
//			updateLocalLinks(neighborAddr,bni->getRouterXPos(),bni->getRouterYPos()); // First updateLocalLinks
			return;
		    }

	}

//    if(IPv4Datagram* packet=dynamic_cast<IPv4Datagram*>(msg))
//        {
//        }


	if(ControlManetRouting* control=dynamic_cast<ControlManetRouting*>(msg))
	    {
		if (control->getOptionCode() == MANET_ROUTE_NOROUTE) // no available route!
		    {
//		    if (myAddr.getDByte(3) == 7)
//		        {
//		        int stop =1;
//		        }
		    std::cout << "node " << myAddr << " receives packet " << control->getName() << "\n";
            IPv4Datagram *datagram= dynamic_cast<IPv4Datagram*>(control->decapsulate());

            std::cout << "Identification is " << datagram->getIdentification() << ", name is " << datagram->getName() << "\n";

            const IPv4Address dst = datagram->getDestAddress();
            Coord dstC(posTable[dst].x,posTable[dst].y);
			const IPv4Address src=control->getSrcAddress().toUint64()==IPv4Address::UNSPECIFIED_ADDRESS.getInt()?myAddr:IPv4Address(control->getSrcAddress().toUint64());

	        double oldDist2Dst = 10000;
	        IPv4Address nexthop;

	        for(nh_t::const_iterator nhIt=neighborhood.begin();nhIt!=neighborhood.end();++nhIt)
	            {
	            Coord neighborC(nhIt->second->getRouterXPos(), nhIt->second->getRouterYPos());

	            double newDist2Dst= neighborC.distance(dstC);
	            if(newDist2Dst < oldDist2Dst)
	                {
	                oldDist2Dst = newDist2Dst;
	                nexthop = nhIt->first;
	                }
	            }
	        std::cout << "Node " << myAddr.getDByte(3) << " decides to send the packet to " << nexthop << " at " << simTime().dbl() <<  "\n";

            datagram->removeControlInfo(); // waiting for transmission

            IPv4ControlInfo *ipControlInfo = new IPv4ControlInfo();
            ipControlInfo->setProtocol(IP_PROT_MANET);
            ipControlInfo->setSrcAddr(myAddr);
            ipControlInfo->setNextHopAddr(nexthop);
            ipControlInfo->setDestAddr(datagram->getDestAddress());
            ipControlInfo->setTimeToLive(1);


            IPv4Datagram * newdatagram= datagram->dup();
            newdatagram->setIdentification(101);
            newdatagram->setTransportProtocol(IP_PROT_MANET);
            newdatagram->setDestAddress(datagram->getDestAddress());
	        newdatagram->setControlInfo(ipControlInfo);
	        float delay=exponential(10e-3);
	        sendDelayed(newdatagram,delay,"to_ip"); //message 'p' is broadcasted, which contains the IP address of the sender, low tx power.


            delete msg;
            return;
            }
	    }

    //start to send beacon:
    if ( msg->isSelfMessage() )
        {
        if(!strcmp(msg->getName(), "beaconing"))
            {
            ev << "It is time to update my neighborhood!" << endl;
            neighborhoodBackup.clear();

            GrNeighborInfo* selfBni = new GrNeighborInfo();
            selfBni->setRouterAddress(myAddr);
            selfBni->setRouterXPos(getXPos());
            selfBni->setRouterYPos(getYPos());
            doLocalBroadcast(selfBni);

            cMessage* beaconing = new cMessage("beaconing");
            scheduleAt(simTime()+ 0.5, beaconing);   // send beacon 1s later

            cMessage* updateNh = new cMessage("updateNh");
            scheduleAt(simTime()+ 0.1, updateNh);   // update neighborhood 0.1s later
            time_updateNh = simTime()+ 0.1;
            delete msg;
            return;
            }
        else
            {
            printf("%d's neighbors:\n", myAddr.getDByte(3));
            std::cout << neighborhood;
            neighborhood = neighborhoodBackup;
            std::cout << neighborhood;

//            updateLocalLinks();

            printf("%s has updated its neighborhood at %f\n\n", myAddr.str().c_str(), simTime().dbl());
            delete msg;
            return;
            }
        }
}

void GR::positionUpdated(double x, double y){
	posTable[myAddr]=Coord(x,y);
    }


uint32_t GR::getRoute(const Uint128&, std::vector<Uint128>&)
    {
	return 0;
    }

bool GR::getNextHop(const Uint128&, Uint128&, int&, double&)
    {
	return false;
    }

void GR::setRefreshRoute(const Uint128&, const Uint128&, bool)
    {
    }

bool GR::isProactive()
    {
	return false;
    }

bool GR::isOurType(cPacket*)
    {
	return false;
    }

bool GR::getDestAddress(cPacket*, Uint128&)
{
	return false;
}

//void GR::finish()
//{
//    // This function is called by OMNeT++ at the end of the simulation.
//}
