// System includes:

// Omnet includes:

// INET includes:
#include "Coord.h"
#include "IMobility.h"
#include "IPv4Datagram.h"
#include "IPv4ControlInfo.h"
#include "ControlManetRouting_m.h"

// Gpsr includes:
#include "gpsr.h"
#include "GpsrRouteRequest_m.h"
#include "GpsrHello_m.h"
#include "GpsrHelloAck_m.h"
#define BEACONING

Define_Module(GPSR);

GPSR::posTable_t GPSR::posTable;

void GPSR::initialize(int stage)
{
	if(stage==4)
	{
	    registerRoutingModule();
		registerPosition(); // We register for position information, but unfortunately we will not get up-to-date information before the first update :( // Di:?? )

		// Determine position and IP:
		routingTable=check_and_cast<IRoutingTable*>(getParentModule()->getSubmodule("routingTable"));
		myAddr=routingTable->getRouterId();
		ev << "GPSR: My (" << myAddr << ") position: (" << getXPos() << "," << getYPos() << ")" << endl;

        IRoutingTable* dstRoutingTable=check_and_cast<IRoutingTable*>(getParentModule()->getParentModule()->getModuleByRelativePath("fixhost[12]")->getSubmodule("routingTable"));
        dstAddr = dstRoutingTable->getRouterId();

		// Broadcast position information to neighbors:
		GpsrNeighborInfo* bni=new GpsrNeighborInfo();
		bni->setRouterAddress(myAddr);
		bni->setRouterXPos(getXPos()); //record the current position
		bni->setRouterYPos(getYPos());
		doLocalBroadcast(bni);
#ifndef BEACONING;//update neighborhood
        cMessage *beaconing = new cMessage("beaconing");
        scheduleAt(0.85, beaconing);
#endif
	}
}

void GPSR::doLocalBroadcast(cPacket *pk)
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
	p->encapsulate(pk); //pk, here is of GpsrNeighborInfo, is encapsulated in a IPv4Datagram pointed by 'p'.
	float delay=exponential(10e-3);
	sendDelayed(p,delay,"to_ip"); //message 'p' is broadcasted, which contains the IP address of the sender, low tx power.
}

void GPSR::doGlobalBroadcast(cPacket *pk) //purpose of this global broadcast:
{
	IPv4Datagram* p=new IPv4Datagram();
	p->setSrcAddress(myAddr);
	p->setDestAddress(IPv4Address::ALLONES_ADDRESS);
	p->setTimeToLive(1);
	p->setTransportProtocol(IP_PROT_MANET);
	IPv4ControlInfo *ipControlInfo = new IPv4ControlInfo();
	ipControlInfo->setProtocol(IP_PROT_MANET);
	ipControlInfo->setSrcAddr(myAddr);
	ipControlInfo->setDestAddr(IPv4Address::ALLONES_ADDRESS);
	ipControlInfo->setTimeToLive(1);
	ipControlInfo->setTransmitterPower(20);
	p->setControlInfo(ipControlInfo);
	p->encapsulate(pk);
	float delay=exponential(10e-3);
	sendDelayed(p,delay,"to_ip"); //message 'p' is broadcasted, which contains the IP address of the sender, high tx power.
}

void GPSR::handleMessage(cMessage *msg) //class SIM_API cPacket : public cMessage
{
	if(GpsrNeighborInfo* bni=dynamic_cast<GpsrNeighborInfo*>(msg))
	{
		const IPv4Address neighborAddr=bni->getRouterAddress();
		//printf("Gpsr: %s received message (%s,%f,%f)\n", myAddr.str().c_str(), neighborAddr.str().c_str(), bni->getRouterXPos(), bni->getRouterYPos());

		// from myself
		if(neighborAddr == myAddr)
		{
			ev << "GPSR: Discarding neighbor info from myself" << endl;
			delete bni;
			return;
		}

        /*
         * restore received neighbor information which will be cleared every beaconing interval
         */
        if(neighborAddr!=myAddr)
            {
            neighborhoodBackup[neighborAddr]=bni;
            }

		nh_t::const_iterator it=neighborhood.find(neighborAddr);//      typedef std::tr1::unordered_map<IPv4Address,GpsrNeighborInfo*,hashIPv4Address> nh_t;

		// Entry exists (the first condition below shows that the iterator (it) doesn't point to map::end), no update:
		if(it!=neighborhood.end() && equal(*(*it).second, *bni))
		{
			ev << "GPSR: Entry already exists, discarding" << endl;
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

		// Question: Is the following necessary? node has no idea of s-d, how to form local link?
		// Entry does not exist:
		neighborhood[neighborAddr]=bni;
//		updateLocalLinks(neighborAddr,bni->getRouterXPos(),bni->getRouterYPos()); // First updateLocalLinks
		return;
	}


	if(ControlManetRouting* control=dynamic_cast<ControlManetRouting*>(msg))
	{
		if (control->getOptionCode()==MANET_ROUTE_NOROUTE) //Di: no available route, find route!
		{
	        ev << "=============Broadcast starts!============" << endl; // to see
			const IPv4Address src=control->getSrcAddress().toUint64()==IPv4Address::UNSPECIFIED_ADDRESS.getInt()?myAddr:IPv4Address(control->getSrcAddress().toUint64());
			const IPv4Address dst=IPv4Address(control->getDestAddress().toUint64());
			GpsrRouteRequest* rreq=new GpsrRouteRequest(); // build a route request!
			rreq->setSrc(src);
			if(src==myAddr) // only true with respect to source node
			    {
				rreq->setSrcPos(Coord(getXPos(),getYPos()));
			    }
			else
			    {
				rreq->setSrcPos(Coord(posTable[src].x,posTable[src].y));
			    }
			rreq->setDst(dst);
			rreq->setDstPos(Coord(posTable[dst].x,posTable[dst].y));
			ev << "GPSR: " << myAddr << ": sending rreq (" << rreq->getSrc() << "," << rreq->getDst() << ") at " << simTime() << "!" << endl;

			scheduleAt(simTime(),rreq);
		}

//        /*
//         *  all nodes except for dst, find next hop is not within its neighborhood
//         */
//		IPv4Route* previousRoute = routingTable -> findBestMatchingRoute(dst);
//        nh_t::iterator It = neighborhood.find(gw2);
//        if ( (gw2.getDByte(3)!=0 && It == neighborhood.end()) && myAddr.getDByte(3)!=2 )
//            {
//            printf("============= %s is to transmit at %f but next hop node moves away ! ============\n", myAddr.str().c_str(), simTime().dbl());
//            printf("%s's gw2 is %d, and neighbors are:\n", myAddr.str().c_str(), gw2.getDByte(3));
//            for (nh_t::iterator It = neighborhood.begin(); It!=neighborhood.end(); ++It)
//                {
//                printf("%d \t", It->first.getDByte(3));
//                }
//            printf("\n");
//
//            //TODO: this chunk is only for one s-d pair
//            for(sdPairs_t::const_iterator sdPairsIt=sdPairs.begin(); sdPairsIt!=sdPairs.end(); ++sdPairsIt)
//                {
//                const IPv4Address src = sdPairsIt->first.src;
//                const IPv4Address dst = sdPairsIt->first.dst;
//
//                BergerRouteRequest* rreq=new BergerRouteRequest(); // build a route request!
//                rreq->setSrc(src);
//                rreq->setSrcPos(Coord(posTable[src].x,posTable[src].y));
//                rreq->setDst(dst);
//                rreq->setDstPos(Coord(posTable[dst].x,posTable[dst].y));
//                ev << "BERGER: " << myAddr << ": sending global rreq (" << rreq->getSrc() << "-->" << rreq->getDst() << ") at " << simTime() << "!" << endl;
//                printf("Berger: %s sending rreq (%s,--> %s) to repair the broken link at %f !\n", myAddr.str().c_str(), rreq->getSrc().str().c_str(), rreq->getDst().str().c_str(), simTime().dbl());
//
//                numRepairBroadcast[myAddr] ++;
//                doLocalBroadcast(rreq);
//                printf("Broadcast from %s\n", myAddr.str().c_str());
//                }
//            }

		delete control;
		return;
	}

	// intrigued by the arrival of global routing message!
	if(GpsrRouteRequest* rreq=dynamic_cast<GpsrRouteRequest*>(msg))
	    {
		ev << "GPSR: " << myAddr << ": got rreq (" << rreq->getSrc() << "," << rreq->getDst() << ") at " << simTime() << "!" << endl;
		const sdPairKey sdpk(rreq->getSrc(),rreq->getDst());
		const sdPairValue sdpv(rreq->getSrcPos(),rreq->getDstPos());
		sdPairs[sdpk]=sdpv;
		updateLocalLinks();
		delete rreq;
		return;
	    }

    //start to send beacon:
    if ( msg->isSelfMessage() )
        {
        if(!strcmp(msg->getName(), "beaconing"))
            {
            ev << "It is time to update my neighborhood!" << endl;
            neighborhoodBackup.clear();

            GpsrNeighborInfo* selfBni = new GpsrNeighborInfo();
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

            updateLocalLinks();

            printf("%s has updated its neighborhood at %f\n\n", myAddr.str().c_str(), simTime().dbl());
            delete msg;
            return;
            }
        }

}

void GPSR::positionUpdated(double x, double y)
    {
	posTable[myAddr]=Coord(x,y);
    }

//// decide two half routes, but how does every node know s-d pairs?
//void GPSR::updateLocalLinks(const IPv4Address& updatedNeighbor, double nbX, double nbY)
//{
//	ev << "GPSR: " << myAddr << " looks for better links through " << updatedNeighbor << endl;
//	for(sdPairs_t::const_iterator sdPairsIt=sdPairs.begin();sdPairsIt!=sdPairs.end();++sdPairsIt)
//	{
//		double oldQuality=0;
//		ll_t::const_iterator llIt=localLinks.find(sdPairsIt->first);//as to current sd pair, whether its local link exist
//		if(llIt!=localLinks.end()) // exist
//		{
//			oldQuality=llIt->second.quality;
//		}
//		for(nh_t::const_iterator nhIt=neighborhood.begin();nhIt!=neighborhood.end();++nhIt)
//		{
//			const GpsrNodeInfo src=GpsrNodeInfo(sdPairsIt->first.src,sdPairsIt->second.srcPos.x,sdPairsIt->second.srcPos.y);
//			const GpsrNodeInfo dst=GpsrNodeInfo(sdPairsIt->first.dst,sdPairsIt->second.dstPos.x,sdPairsIt->second.dstPos.y);
//			const GpsrNodeInfo oldNb=GpsrNodeInfo(nhIt->second->getRouterAddress(),nhIt->second->getRouterXPos(),nhIt->second->getRouterYPos());
//			const GpsrNodeInfo newNb=GpsrNodeInfo(updatedNeighbor, nbX, nbY);
//			const GpsrNodeInfo self=GpsrNodeInfo(myAddr,getXPos(),getYPos());
//			double newQuality=calculateLocalLinkQuality(src,oldNb,self,newNb,dst); //current: based on the length
//			if(newQuality>oldQuality)
//			{
//				ev << "GPSR: Updating local link: " << sdPairsIt->first.src << "<->" << nhIt->second->getRouterAddress() << "<->" << myAddr << "<->" << updatedNeighbor << "<->" << sdPairsIt->first.dst << endl;
//				// parameters: sourse address, a neighbor's address, new discovered neighbor, destination address, quality!
//				updateRoute(sdPairsIt->first.src,nhIt->second->getRouterAddress(),updatedNeighbor,sdPairsIt->first.dst,newQuality);
//				oldQuality=newQuality;
//			}
//			newQuality=calculateLocalLinkQuality(src,newNb,self,oldNb,dst);
//			if(newQuality>oldQuality)
//			{
//				ev << "GPSR: Updating local link: " << sdPairsIt->first.src << "<->" << updatedNeighbor << "<->" << myAddr << "<->" << nhIt->second->getRouterAddress() << "<->" << sdPairsIt->first.dst << endl;
//				updateRoute(sdPairsIt->first.src,updatedNeighbor,nhIt->second->getRouterAddress(),sdPairsIt->first.dst,newQuality);
//				oldQuality=newQuality;
//			}
//		}
//	}
//}

void GPSR::updateLocalLinks() //overload
    {
    for(sdPairs_t::const_iterator sdPairsIt=sdPairs.begin();sdPairsIt!=sdPairs.end();++sdPairsIt)
        {
        const GpsrNodeInfo src = GpsrNodeInfo(sdPairsIt->first.src, sdPairsIt->second.srcPos.x, sdPairsIt->second.srcPos.y); // info about gw is not for sure
        const GpsrNodeInfo dst = GpsrNodeInfo(sdPairsIt->first.dst, sdPairsIt->second.dstPos.x, sdPairsIt->second.dstPos.y);
        const GpsrNodeInfo self = GpsrNodeInfo(myAddr,getXPos(),getYPos());
        ev << "GPSR: " << myAddr << " looks for better links from " << src << " to " << dst << endl;
        double oldQuality = 1000000;
        ll_t::const_iterator llIt = localLinks.find(sdPairKey(src.ip,dst.ip));
        if(llIt!=localLinks.end())
            {
            oldQuality=llIt->second.quality;
            }

        // decide parent/children neighbors
        Coord srcC(src.x,src.y);
        Coord dstC(dst.x,dst.y);
        Coord selfC(getXPos(),getYPos());

        for(nh_t::const_iterator It=neighborhood.begin(); It!=neighborhood.end(); ++It)
            {
            int id = It->first.getDByte(3);
            Coord nbC(It->second->getRouterXPos(), It->second->getRouterYPos());

            if (dstC.distance(nbC)<= dstC.distance(selfC) || It->first == dst.ip)
                {
                children[It->first] = It->second;
                }
             }

        std::cout << "BERGER: Node " << myAddr.getDByte(3) << " (" << neighborhood.size() << ": " << neighborhood << ", children set: " << children << "), forms local links for the first time, from " << src << " to " << dst << endl;



        if(children.size())
        {
            for(nh_t::const_iterator bIt=children.begin();bIt!=children.end();++bIt)    //look for b\in D_i
                {
                const GpsrNodeInfo b=GpsrNodeInfo(bIt->second->getRouterAddress(),bIt->second->getRouterXPos(),bIt->second->getRouterYPos());
                const GpsrNodeInfo self=GpsrNodeInfo(myAddr,getXPos(),getYPos());
                double newQuality = calculateLocalLinkQuality(b,dst);
                if(newQuality < oldQuality)
                    {
                    std::cout << "GPSR: Updating local link: " << myAddr << "<->" << bIt->second->getRouterAddress() << "<->" << dst.ip << endl;
                    updateRoute(src.ip, IPv4Address::UNSPECIFIED_ADDRESS, b.ip, dst.ip, newQuality);
                    oldQuality = newQuality;
                    }
                }
        }
        if(!children.size())
            for(nh_t::const_iterator bIt=neighborhood.begin();bIt!=neighborhood.end();++bIt)    //TODO: exclude the upstream node
                {
                const GpsrNodeInfo b=GpsrNodeInfo(bIt->second->getRouterAddress(),bIt->second->getRouterXPos(),bIt->second->getRouterYPos());
                const GpsrNodeInfo self=GpsrNodeInfo(myAddr,getXPos(),getYPos());
                double newQuality = calculateLocalLinkQuality(b,dst);
                if(newQuality < oldQuality)
                    {
                    std::cout << "GPSR: Updating local link: " << myAddr << "<->" << bIt->second->getRouterAddress() << "<->" << dst.ip << endl;
                    updateRoute(src.ip, IPv4Address::UNSPECIFIED_ADDRESS, b.ip, dst.ip, newQuality);
                    oldQuality = newQuality;
                    }
                }
        }
    }

void GPSR::updateRoute(const IPv4Address& src, const IPv4Address& a, const IPv4Address& b, const IPv4Address& dst, double quality)
{
	localLinks[sdPairKey(src,dst)]=LLValue(a,b,quality);

	// remove the previous route:
    IPv4Route* previousRoute = routingTable -> findBestMatchingRoute(dst);
	routingTable -> removeRoute(previousRoute);

	// Add new routes:
	IPv4Route* pathToDst=new IPv4Route();
	pathToDst->setDestination(dst);
	pathToDst->setNetmask(IPv4Address("255.255.255.255"));
	pathToDst->setGateway(b);
	pathToDst->setInterface(routingTable->getInterfaceByAddress(myAddr));
	pathToDst->setSource(IPv4Route::MANET);
	pathToDst->setMetric(quality);
	routingTable->addRoute(pathToDst);

}

double GPSR::calculateLocalLinkQuality(const GpsrNodeInfo& b, const GpsrNodeInfo& dst) const
{
	ev << "GPSR: Calculating quality for local link "  << b << "<->" << dst << endl;
	Coord bC(b.x,b.y);
	Coord dstC(dst.x,dst.y);
//	double length=bC.distance(dstC);
//	ev << "GPSR:: l=" << length << endl;
//	return length;

    /*
     * we use delay as metric
     */

    double transmitterPower=par("transmitterPower");
    double thermalNoise=par("thermalNoise"); //-110dbm, conversion to w is done in function calculateLocalLinkQuality()
    double pathLossAlpha=par("pathLossAlpha");
    int messageLength=par("messageLength");
    int bandwidth = par("bandwidth"); //22 MHz

    double delay, r;

    thermalNoise = pow(10,     thermalNoise/10)/1000;

    double snr = transmitterPower * pow(bC.distance(dstC), (-pathLossAlpha))/pow(thermalNoise,2);
    delay = messageLength / (bandwidth* log2(1+snr));
    double wayToGo = bC.distance(dstC);//distance to dst
    r= delay*wayToGo;
    std::cout << "GPSR: Node " << myAddr.getDByte(3) << "'s delay= " << delay << ". utility= " << r << endl;
    return r;




}

uint32_t GPSR::getRoute(const Uint128&, std::vector<Uint128>&)
{
	return 0;
}

bool GPSR::getNextHop(const Uint128&, Uint128&, int&, double&)
{
	return false;
}

void GPSR::setRefreshRoute(const Uint128&, const Uint128&, bool)
{
}

bool GPSR::isProactive()
{
	return false;
}

bool GPSR::isOurType(cPacket*)
{
	return false;
}

bool GPSR::getDestAddress(cPacket*, Uint128&)
{
	return false;
}

void GPSR::finish()
{
    // This function is called by OMNeT++ at the end of the simulation.
    if (myAddr.getDByte(3) == dstAddr.getDByte(3))
        {
        double pathLength = par("pathLength");
        std::string resultFileName = par("resultFileName");
        resultFileName+= "_pathLength.csv";
        const char * resultFileNamechar = resultFileName.c_str();

        std::ofstream fileio;
        fileio.open (resultFileNamechar, std::ios::app);
        if (fileio.is_open())
            {
            fileio << "pathLength: " << ";" << pathLength << "\n";
            fileio.flush();
            fileio.close();
            fileio <<std::endl;
            }
        }
}
