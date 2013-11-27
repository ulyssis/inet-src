// System includes:

// Omnet includes:

// INET includes:

#include "Coord.h"
#include "IMobility.h"
#include "IPv4Datagram.h"
#include "IPv4ControlInfo.h"
#include "ControlManetRouting_m.h"

// Berger includes:
#include "berger.h"
#include "BergerRouteRequest_m.h"
#include <math.h>       /* log2 */


Define_Module(BERGER);

BERGER::posTable_t BERGER::posTable;
Coord srcPos;
Coord dstPos;
IPv4Address srcAddr, dstAddr;
double lambda=1.0e-2;
double transmitterPower=6e-4;
double thermalNoise=-110; //-110dbm, conversion to w is done in function calculateLocalLinkQuality()
double pathLossAlpha=2;
int messageLength=512;
int bandwidth = 2.2e+7; //22 MHz


void BERGER::initialize(int stage)
{
	if(stage==4)
	{
		registerRoutingModule();
		registerPosition(); // We register for position information, but unfortunately we will not get up-to-date information before the first update :(

		Radio * myRadio=check_and_cast<Radio*>(getParentModule()->getModuleByRelativePath(".wlan[0].radio"));
//
        lambda = cSimulation::getActiveSimulation()->getSystemModule()->par("lambda").doubleValue();
//        transmitterPower = cSimulation::getActiveSimulation()->getSystemModule()->getModuleByRelativePath("wlan[0].radio")->par("transmitterPower");
//        thermalNoise = cSimulation::getActiveSimulation()->getSystemModule()->getModuleByRelativePath("wlan[0].radio")->par("thermalNoise");
//        pathLossAlpha = cSimulation::getActiveSimulation()->getSystemModule()->getModuleByRelativePath("wlan[0].radio")->par("pathLossAlpha").doubleValue();
//        messageLength = cSimulation::getActiveSimulation()->getSystemModule()->getModuleByRelativePath("udpApp[0]")->par("messageLength").doubleValue();

		// Determine position and IP:
		routingTable=check_and_cast<IRoutingTable*>(getParentModule()->getSubmodule("routingTable"));
		myAddr=routingTable->getRouterId();
		// Broadcast position information to neighbors:

        BergerNeighborInfo* bni=new BergerNeighborInfo();
        bni->setRouterAddress(myAddr);
        bni->setRouterXPos(getXPos());
        bni->setRouterYPos(getYPos());
        bni->setGw1(IPv4Address::UNSPECIFIED_ADDRESS);
        bni->setGw2(IPv4Address::UNSPECIFIED_ADDRESS);
        doLocalBroadcast(bni);
        cMessage *localBroadcastBni = new cMessage("localBroadcastBni");
        scheduleAt(0.1, localBroadcastBni);


		/*
		 * src broadcasts rreq
		 */
#ifdef use_rreqMsg
        IRoutingTable* srcRoutingTable=check_and_cast<IRoutingTable*>(getParentModule()->getParentModule()->getModuleByRelativePath("fixhost[40]")->getSubmodule("routingTable"));
        srcAddr = srcRoutingTable->getRouterId();
        srcPos.x =posTable[srcAddr].x;
        srcPos.y = posTable[srcAddr].y;
        double test = srcPos.x;


        IRoutingTable* dstRoutingTable=check_and_cast<IRoutingTable*>(getParentModule()->getParentModule()->getModuleByRelativePath("fixhost[12]")->getSubmodule("routingTable"));
        dstAddr = dstRoutingTable->getRouterId();
        dstPos.x =posTable[dstAddr].x;
        dstPos.y = posTable[dstAddr].y;

        std::cout << "BERGER::src and dst'location: " << dstAddr.getDByte(3) << ":("<< srcPos.x << "," << srcPos.y << "), " << srcAddr.getDByte(3) << ":(" << dstPos.x << "," << dstPos.y << ")\n";

        //rreqMsg is generated on the src node which will be broadcasted to neighbors
		if (myAddr.equals(srcAddr))
            {
            BergerRouteRequest* rreqMsg=new BergerRouteRequest();
            rreqMsg->setSrc(srcAddr);
            Coord srcPosC(srcPos.x, srcPos.y);
            rreqMsg->setSrcPos(srcPosC);

            rreqMsg->setDst(dstAddr);
            Coord dstPosC(dstPos.x, dstPos.y);
            rreqMsg->setDstPos(dstPosC);

            scheduleAt(10, rreqMsg);
            }
#endif
	}
}


void BERGER::doLocalBroadcast(cPacket *pk)
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
	p->setControlInfo(ipControlInfo);
	p->encapsulate(pk);
	float delay=exponential(10e-3);
	sendDelayed(p,delay,"to_ip");
}

void BERGER::doGlobalBroadcast(cPacket *pk)
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
	sendDelayed(p,delay,"to_ip");
}

void BERGER::handleMessage(cMessage *msg)
{
	if(BergerNeighborInfo* bni=dynamic_cast<BergerNeighborInfo*>(msg))
	{
		const IPv4Address neighborAddr=bni->getRouterAddress();
		//printf("Berger: %s received message (%s,%f,%f)\n", myAddr.str().c_str(), neighborAddr.str().c_str(), bni->getRouterXPos(), bni->getRouterYPos());

		// from myself
		if(neighborAddr==myAddr)
		{
//			std::cout << "BERGER: Discarding neighbor info from myself" << endl;
			delete bni;
			return;
		}

		nh_t::const_iterator it=neighborhood.find(neighborAddr);

		// Entry exists, no update:
		if(it!=neighborhood.end() && equal(*(*it).second,*bni))
		{
//		    std::cout << "BERGER: Entry already exists, discarding" << endl;
			delete bni;
			return;
		}

		// node exists in neighborhood already, update:
		if(it!=neighborhood.end())
		{
			// delete old entry:
			delete (*it).second;
			// insert new entry:
			neighborhood[neighborAddr]=bni;

			/*
			 *  update local links, after rreq is broadcasted from src (sdPairs on node which has received rreq is not empty)
			 *  this will be processed after rreq is received and sdPairs are available on any node
			 */
	        if(parents.size() * children.size()>=1)
	            {
	            updateLocalLinks(bni);
	            }
			return;
		}

		// node does not exist yet:
		neighborhood[neighborAddr]=bni;
		if(parents.size() * children.size()>=1)
		    {
		    updateLocalLinks(bni);
		    }

		return;
	}

	/*
	 * this function is not processed if rreqMsg is used to initialize the link formation process
	 */
	if(ControlManetRouting* control=dynamic_cast<ControlManetRouting*>(msg))
	{
		if (control->getOptionCode()==MANET_ROUTE_NOROUTE)
		{
			const IPv4Address src=control->getSrcAddress().toUint64()==IPv4Address::UNSPECIFIED_ADDRESS.getInt()?myAddr:IPv4Address(control->getSrcAddress().toUint64());
			const IPv4Address dst=IPv4Address(control->getDestAddress().toUint64());
			BergerRouteRequest* rreq=new BergerRouteRequest();
			rreq->setSrc(src);
			if(src==myAddr)
			{
				rreq->setSrcPos(Coord(getXPos(),getYPos()));
			}
			else
			{
				rreq->setSrcPos(Coord(posTable[src].x,posTable[src].y));
			}
			rreq->setDst(dst);
			rreq->setDstPos(Coord(posTable[dst].x,posTable[dst].y));
			std::cout << "BERGER: " << myAddr << ": sending rreq (" << rreq->getSrc().getDByte(3) << "," << rreq->getDst().getDByte(3) << ") at " << simTime() << " because of MANET_ROUTE_NOROUTE" << "!" << endl;
			doGlobalBroadcast(rreq);
		}
		delete control;
		return;
	}

	/*
	 * NOTE: if sdpair contains more than one s-d, do this, if multiple, codes need modification
	 */
	if(BergerRouteRequest* rreq=dynamic_cast<BergerRouteRequest*>(msg))
	{
	    if(myAddr.getDByte(3)==15)
	        {
	        int stop2 =1;
	        }
	    if (!sdPairs.size())
	    {
	        if(msg->isSelfMessage())
	            {
	            std::cout << "BERGER: " << myAddr.getDByte(3) << ": sends rreqMsg (" << rreq->getSrc().getDByte(3) << ": (" << rreq->getSrcPos().x << "," << rreq->getSrcPos().y << "), " << rreq->getDst().getDByte(3) << ":("<<rreq->getSrcPos().x << "," << rreq->getSrcPos().y << "), at time " << simTime() << "s!" << std::endl;
	            }
	        else
	            {
	            std::cout << "BERGER: " << myAddr << ": gets rreqMsg (" << rreq->getSrc().getDByte(3) << "-" << rreq->getDst().getDByte(3) << ") at " << simTime() << "!" << endl;
	            }
            const sdPairKey sdpk(rreq->getSrc(),rreq->getDst());
            const sdPairValue sdpv(rreq->getSrcPos(),rreq->getDstPos());
            sdPairs[sdpk] = sdpv;//TODOTODO

            std::cout << "BERGER: " << sdPairs.size() << "\n";
            sdPairs_t::const_iterator pairIt = sdPairs.find(sdpk);
            if(pairIt != sdPairs.end()) //this s-d pair contained in the rreq is not seen yet
                {
                sdPairs[sdpk]=sdpv;
                const BergerNodeInfo src=BergerNodeInfo(rreq->getSrc(),rreq->getSrcPos().x,rreq->getSrcPos().y,IPv4Address::UNSPECIFIED_ADDRESS,IPv4Address::UNSPECIFIED_ADDRESS);
                const BergerNodeInfo dst=BergerNodeInfo(rreq->getDst(),rreq->getDstPos().x,rreq->getDstPos().y,IPv4Address::UNSPECIFIED_ADDRESS,IPv4Address::UNSPECIFIED_ADDRESS);
                updateLocalLinks(src, dst);
    //            updateLocalLinks(BergerNodeInfo(rreq->getSrc(),rreq->getSrcPos().x,rreq->getSrcPos().y),
    //                             BergerNodeInfo(rreq->getDst(),rreq->getDstPos().x,rreq->getDstPos().y));
                //TODO: notify others when updates
                BergerRouteRequest* newrreq = rreq->dup();
        #ifdef use_rreqMsg
                doLocalBroadcast(newrreq);
                std::cout << "BERGER: node " << myAddr.getDByte(3) <<" broadcast MSGrreq at " << simTime() << "\n";
        #endif
                delete rreq;
                }
            else
                {
                delete rreq;
                }
            return;
	    }
	}

	if ( msg->isSelfMessage() && (!strcmp(msg->getName(), "localBroadcastBni")) && simTime() < 10)
	    {
        std::cout << "BERGER: Node (" << myAddr.getDByte(3) << ")' position: (" << getXPos() << "," << getYPos() << "), broadcasting localBroadcastBni at "<<simTime() << endl;
        BergerNeighborInfo* bni=new BergerNeighborInfo();
        bni->setRouterAddress(myAddr);
        bni->setRouterXPos(getXPos());
        bni->setRouterYPos(getYPos());
        bni->setGw1(IPv4Address::UNSPECIFIED_ADDRESS);
        bni->setGw2(IPv4Address::UNSPECIFIED_ADDRESS);
        doLocalBroadcast(bni);

        cMessage *localBroadcastBni = msg->dup();
        scheduleAt(simTime()+2, localBroadcastBni);
        delete msg;
	    }
}

void BERGER::positionUpdated(double x, double y)
{
	posTable[myAddr]=Coord(x,y);
}

/*
 *  update local link after receiving new *bni, just compare the utility with this new nh with the old one
 *  TODO
 */
//void BERGER::updateLocalLinks(const IPv4Address& updatedNeighbor, double nbX, double nbY)
void BERGER::updateLocalLinks(BergerNeighborInfo* bni)
{
    if (gw1 != IPv4Address::UNSPECIFIED_ADDRESS && gw2 != IPv4Address::UNSPECIFIED_ADDRESS) //
    {
        std::cout << "BERGER: " << myAddr.getDByte(3) << " knows neighbor " << bni->getRouterAddress().getDByte(3) <<" has new state, looks for better links through " << bni->getRouterAddress().getDByte(3) << " at time " << simTime() << "\n";
        for(sdPairs_t::const_iterator sdPairsIt=sdPairs.begin();sdPairsIt!=sdPairs.end();++sdPairsIt)
        {
            double oldQuality=0;
            ll_t::const_iterator llIt=localLinks.find(sdPairsIt->first);
            if(llIt!=localLinks.end())
            {
                oldQuality = llIt->second.quality;
            } // retrieve old utility of node


            // dont consider src and dst
            if (sdPairsIt->first.src != myAddr && sdPairsIt->first.dst != myAddr)
            {
                nh_t::const_iterator nhIt1 = parents.find(bni->getRouterAddress());
                nh_t::const_iterator nhIt2 = children.find(bni->getRouterAddress());

                // this new nh is a parent node, and different from current gw1
                if (nhIt1 !=parents.end() && bni->getRouterAddress() != gw1)
                {
                    const BergerNodeInfo src = BergerNodeInfo(sdPairsIt->first.src,sdPairsIt->second.srcPos.x,sdPairsIt->second.srcPos.y, IPv4Address::UNSPECIFIED_ADDRESS,IPv4Address::UNSPECIFIED_ADDRESS);
                    const BergerNodeInfo dst = BergerNodeInfo(sdPairsIt->first.dst,sdPairsIt->second.dstPos.x,sdPairsIt->second.dstPos.y, IPv4Address::UNSPECIFIED_ADDRESS, IPv4Address::UNSPECIFIED_ADDRESS);
                    const BergerNodeInfo childNode = BergerNodeInfo(gw2, neighborhood[gw2]->getRouterXPos(), neighborhood[gw2]->getRouterYPos(), neighborhood[gw2]->getGw1(), neighborhood[gw2]->getGw2());
                    const BergerNodeInfo newParentNode = BergerNodeInfo(bni->getRouterAddress(), bni->getRouterXPos(),bni->getRouterYPos(),bni->getGw1(),bni->getGw2());
                    const BergerNodeInfo self = BergerNodeInfo(myAddr,getXPos(),getYPos(), gw1, gw2);
                    pair_t pair = calculateLocalLinkQuality(src,newParentNode,self,childNode,dst);
                    double newQuality = pair.second;
                    if(newQuality < oldQuality)
                    {
                        std::cout << "BERGER: Updating local link: " << sdPairsIt->first.src << "<->" << bni->getRouterAddress().getDByte(3) << "<->" << myAddr << "<->" << gw2 << "<->" << sdPairsIt->first.dst << endl;
                        updateRoute(sdPairsIt->first.src,bni->getRouterAddress(),gw2,sdPairsIt->first.dst,newQuality);
                        oldQuality=newQuality;
                        state = pair;
                    }
                }


                // this new nh is a child node, and differs current gw2
                if (nhIt2 != children.end() && bni->getRouterAddress() != gw2)
                {
                    const BergerNodeInfo src=BergerNodeInfo(sdPairsIt->first.src,sdPairsIt->second.srcPos.x,sdPairsIt->second.srcPos.y, IPv4Address::UNSPECIFIED_ADDRESS,IPv4Address::UNSPECIFIED_ADDRESS);
                    const BergerNodeInfo dst=BergerNodeInfo(sdPairsIt->first.dst,sdPairsIt->second.dstPos.x,sdPairsIt->second.dstPos.y, IPv4Address::UNSPECIFIED_ADDRESS, IPv4Address::UNSPECIFIED_ADDRESS);
                    const BergerNodeInfo parentNode = BergerNodeInfo(gw1, neighborhood[gw1]->getRouterXPos(), neighborhood[gw1]->getRouterYPos(), neighborhood[gw1]->getGw1(), neighborhood[gw1]->getGw2());
                    const BergerNodeInfo newChildNode = BergerNodeInfo(bni->getRouterAddress(), bni->getRouterXPos(),bni->getRouterYPos(),bni->getGw1(),bni->getGw2());
                    const BergerNodeInfo self=BergerNodeInfo(myAddr,getXPos(),getYPos(), gw1, gw2);
                    pair_t pair =calculateLocalLinkQuality(src,parentNode,self,newChildNode,dst);
                    double newQuality=pair.first;
                    if(newQuality < oldQuality)
                    {
                        std::cout << "BERGER: First phase updating local link: " << sdPairsIt->first.src << "<->" << gw1 << "<->" << myAddr << "<->" << bni->getRouterAddress().getDByte(3) << "<->" << sdPairsIt->first.dst << endl;
                        updateRoute(sdPairsIt->first.src, bni->getRouterAddress(), gw2, sdPairsIt->first.dst, newQuality);
                        oldQuality = newQuality;
                        state = pair;
                    }
                }
            }
        }
    }
}

/*
 * The action of nodes receiving the rreq
 * Some exceptions:
 * 1. distinguish src, relays and dst
 * 2. if one node's parent set or child set or both are empty, then this node is not going to form local links
 */
void BERGER::updateLocalLinks(const BergerNodeInfo& src, const BergerNodeInfo& dst)
{
	double oldQuality = 10;
	ll_t::const_iterator llIt=localLinks.find(sdPairKey(src.ip,dst.ip));
	if(llIt!=localLinks.end())
	{
		oldQuality=llIt->second.quality;
	}
	if(myAddr.getDByte(3)==6)
	{
	    int stop =1;
	    std::cout << "location: (" << getXPos() << "," << getYPos() << "), " << "(" << src.x << "," << src.y << ")\n";
	}


    // decide parent/children neighbors
	Coord srcC(src.x,src.y);
	Coord dstC(dst.x,dst.y);
	Coord selfC(getXPos(),getYPos());

	for(nh_t::const_iterator It=neighborhood.begin(); It!=neighborhood.end(); ++It)
	    {
	    int id = It->first.getDByte(3);
	    Coord nbC(It->second->getRouterXPos(), It->second->getRouterYPos());
	    double distance0 = srcC.distance(nbC);
	    double distance1 = srcC.distance(selfC);
	    double distance2 = dstC.distance(nbC);
	    double distance3 = dstC.distance(selfC);
        if ((srcC.distance(nbC)<= srcC.distance(selfC) && dstC.distance(nbC) >= dstC.distance(selfC)) || It->first == src.ip)
        {
            parents[It->first] = It->second;
        }
        if ((srcC.distance(nbC)>= srcC.distance(selfC) && dstC.distance(nbC)<= dstC.distance(selfC)) || It->first == dst.ip)
            {
            children[It->first] = It->second;
            }
	    }

    std::cout << "BERGER: Node " << myAddr.getDByte(3) << " (" << neighborhood.size() << ": " << neighborhood << ", parents: " << parents << ", children: " << children << "), forms local links for the first time, from " << src << " to " << dst << endl;

	// src:
	if (src.ip == myAddr)
	    {
        for(nh_t::const_iterator It=children.begin();It!=children.end();++It)
        {
            const BergerNodeInfo b = BergerNodeInfo(It->second->getRouterAddress(),It->second->getRouterXPos(),It->second->getRouterYPos(),IPv4Address::UNSPECIFIED_ADDRESS,IPv4Address::UNSPECIFIED_ADDRESS);
            const BergerNodeInfo self = BergerNodeInfo(myAddr,getXPos(),getYPos(),IPv4Address::UNSPECIFIED_ADDRESS,IPv4Address::UNSPECIFIED_ADDRESS);
            pair_t pair = calculateLocalLinkQuality(src,b,self,b,dst); // a trick here, we actually only need to calculate quality on one link
            double newQuality = pair.second;

            if(newQuality < oldQuality)
            {
                std::cout << "BERGER: First phase updating local link: " << src.ip << "<->" << It->second->getRouterAddress() << "<->" << myAddr << "<->" << It->second->getRouterAddress() << "<->" << dst.ip << endl;

                // in this case, the parent and child node is the same
                updateRoute(src.ip,It->second->getRouterAddress(),It->second->getRouterAddress(),dst.ip,newQuality);
                oldQuality=newQuality;
                state = pair;
            }
	    }
        return;
	    }

    // dst:
    if (dst.ip == myAddr)
        {
        for(nh_t::const_iterator It=parents.begin();It!=parents.end();++It)
        {
            const BergerNodeInfo b=BergerNodeInfo(It->second->getRouterAddress(),It->second->getRouterXPos(),It->second->getRouterYPos(),IPv4Address::UNSPECIFIED_ADDRESS,IPv4Address::UNSPECIFIED_ADDRESS);
            const BergerNodeInfo self=BergerNodeInfo(myAddr,getXPos(),getYPos(),IPv4Address::UNSPECIFIED_ADDRESS,IPv4Address::UNSPECIFIED_ADDRESS);
            pair_t pair=calculateLocalLinkQuality(src,b,self,b,dst); // a trick here, we actually only need to calculate quality on one link
            double newQuality = pair.second;

            if(newQuality < oldQuality)
            {
                std::cout << "BERGER: Updating local link: " << src.ip << "<->" << It->second->getRouterAddress() << "<->" << myAddr << "<->" << It->second->getRouterAddress() << "<->" << dst.ip << endl;
                updateRoute(src.ip,It->second->getRouterAddress(),It->second->getRouterAddress(),dst.ip,newQuality);
                oldQuality=newQuality;
                state = pair;
            }
        }
        return;
        }

    // relays:
    if(parents.size() * children.size() >=1)
    {
//src.ip!= myAddr && dst.ip!=myAddr
        for(nh_t::const_iterator aIt=parents.begin();aIt!=parents.end();++aIt)
        {
            for(nh_t::const_iterator bIt=children.begin();bIt!=children.end();++bIt)
            {
                const BergerNodeInfo a=BergerNodeInfo(aIt->second->getRouterAddress(),aIt->second->getRouterXPos(),aIt->second->getRouterYPos(),IPv4Address::UNSPECIFIED_ADDRESS,IPv4Address::UNSPECIFIED_ADDRESS);
                const BergerNodeInfo b=BergerNodeInfo(bIt->second->getRouterAddress(),bIt->second->getRouterXPos(),bIt->second->getRouterYPos(),IPv4Address::UNSPECIFIED_ADDRESS,IPv4Address::UNSPECIFIED_ADDRESS);
                const BergerNodeInfo self=BergerNodeInfo(myAddr,getXPos(),getYPos(),IPv4Address::UNSPECIFIED_ADDRESS,IPv4Address::UNSPECIFIED_ADDRESS);
                pair_t pair =calculateLocalLinkQuality(src,a,self,b,dst);
                double newQuality = pair.second;
                if(newQuality < oldQuality)
                {
                    std::cout << "BERGER: Updating local link: " << src.ip << "<->" << aIt->second->getRouterAddress() << "<->" << myAddr << "<->" << bIt->second->getRouterAddress() << "<->" << dst.ip << endl;
                    updateRoute(src.ip,aIt->second->getRouterAddress(),bIt->second->getRouterAddress(),dst.ip,newQuality);
                    oldQuality=newQuality;
                    state = pair;
                }
            }
        }
    }

    // broadcast new *bni after forming local link
    BergerNeighborInfo* bni=new BergerNeighborInfo();
    bni->setRouterAddress(myAddr);
    bni->setRouterXPos(getXPos());
    bni->setRouterYPos(getYPos());
    bni->setGw1(gw1);
    bni->setGw2(gw2);
    doLocalBroadcast(bni);
}


BERGER::pair_t BERGER::calculateLocalLinkQuality(const BergerNodeInfo& src, const BergerNodeInfo& a, const BergerNodeInfo& self, const BergerNodeInfo& b, const BergerNodeInfo& dst) const
{
    std::cout << "BERGER: Calculating quality for local link " << src.ip.getDByte(3) << "<->" << a.ip.getDByte(3) << "<->" << self.ip.getDByte(3) << "<->" << b.ip.getDByte(3) << "<->" << dst.ip.getDByte(3) << endl;
    Coord srcC(src.x,src.y);
    Coord aC(a.x,a.y);
    Coord selfC(self.x,self.y);
    Coord bC(b.x,b.y);
    Coord dstC(dst.x,dst.y);
//    double length=srcC.distance(aC)+aC.distance(selfC)+selfC.distance(bC)+bC.distance(dstC);
    /*
     * we use delay as metric
     */
    double delay, r;
    pair_t twoValues;

    thermalNoise = pow(10,     thermalNoise/10)/1000;
    if (self.ip == src.ip || self.ip == dst.ip)
        {
        //TODO: calculate on hop link a-self
        double snr = transmitterPower * pow(aC.distance(selfC), (-pathLossAlpha))/pow(thermalNoise,2);
        delay = messageLength / (bandwidth* log2(1+snr));
        double wayToGo = (self.ip == src.ip)?aC.distance(dstC):aC.distance(srcC);//distance to dst
        r= delay*wayToGo;
        r-= lambda;
        std::cout << "BERGER: Node " << myAddr.getDByte(3) << "'s utility= " << r << endl;
        twoValues.first = delay;
        twoValues.second = r;
        return twoValues;
        }
    else
        {
        /*double transmitterPower;
        double thermalNoise;
        double pathLossAlpha;
        int messageLength;
        int bandwidth;
        */
        /*
         * calculate delay: 1/r
         * r is service rate, 1/r is the average transmission time on the link (delay), which is the metric denoting the link quality
         *  r = C/B = (W*log2(1+v_{k,k+1}))/B
         *  C is capacity, C is measured in bits per second if the logarithm is taken in base 2, B is packet size (messageLength)
         *  W is bandwidth
         */
        double snr1 = transmitterPower * pow(aC.distance(selfC), (-pathLossAlpha))/pow(thermalNoise,2);
        double snr2 = transmitterPower * pow(bC.distance(selfC), (-pathLossAlpha))/pow(thermalNoise,2);
        delay = messageLength / (bandwidth* log2((1+snr1)*(1+snr2)));

        double wayToGo = aC.distance(srcC);
        double wayGone = bC.distance(dstC);

        r = delay*(wayToGo + wayGone);

        if(a.gw2 == self.gw1)
            {
            r=delay-lambda;
            }
        if(b.gw1 == self.gw2)
            {
            r=delay-lambda;
            }
        std::cout << "BERGER: Node " << myAddr.getDByte(3) << "'s utility= " << r << endl;

        twoValues.first = delay;
        twoValues.second = r;

        return twoValues;
        }


}

void BERGER::updateRoute(const IPv4Address& src, const IPv4Address& a, const IPv4Address& b, const IPv4Address& dst, double quality)
{
	localLinks[sdPairKey(src,dst)]=LLValue(a,b,quality);

	// TODO: Remove old routes to src and dst
    IPv4Route* previousRoute1 = routingTable -> findBestMatchingRoute(src);
    routingTable -> removeRoute(previousRoute1);
    IPv4Route* previousRoute2 = routingTable -> findBestMatchingRoute(dst);
    routingTable -> removeRoute(previousRoute2);


	// Add new routes:
	IPv4Route* pathToDst=new IPv4Route();
	pathToDst->setDestination(dst);
	pathToDst->setNetmask(IPv4Address("255.255.255.255"));
	pathToDst->setGateway(b);
	pathToDst->setInterface(routingTable->getInterfaceByAddress(myAddr));
	pathToDst->setSource(IPv4Route::MANET);
	pathToDst->setMetric(quality);
	routingTable->addRoute(pathToDst);


	IPv4Route* pathToSrc=new IPv4Route();
	pathToSrc->setDestination(src);
	pathToSrc->setNetmask(IPv4Address("255.255.255.255"));
	pathToSrc->setGateway(a);
	pathToSrc->setInterface(routingTable->getInterfaceByAddress(myAddr));
	pathToSrc->setSource(IPv4Route::MANET);
	pathToSrc->setMetric(quality);
	routingTable->addRoute(pathToSrc);

	gw1=a;
    gw2=b;
}

void BERGER::finish()
    {
//    int sumHopNum=0;
//    int averageHopNum =0;
//    if(lsit_numberHops.size())
//        {
//        for(Record_numHops::iterator it = lsit_numberHops.begin(); it != lsit_numberHops.end(); it++ )
//            {
//            sumHopNum += *it;
//            }
//        averageHopNum = sumHopNum/lsit_numberHops.size();
//        }

    std::string resultFileName = par("resultFileName");
    resultFileName+="_basic.csv";
    const char * resultFileNamechar = resultFileName.c_str();

    std::ofstream fileio;
    fileio.open (resultFileNamechar, std::ios::app);
//    int numForwarded = getParentModule()->getSubmodule("networkLayer")->getSubmodule("ip")->par("numForwarded_berger_ned");
//    int numUDPPassedUp;

//    // exclude the host nodes which don't have udp submodule
//    if (myAddr.getDByte(3)<3)
//        {
//        numUDPPassedUp = getParentModule()->getSubmodule("udp")->par("numPassedUp_berger_ned");
//        }
//    else
//        {
//        numUDPPassedUp = 0;
//        }
    //    int numForwarded = IPv4_berger->numForwarded_berger; // use the pointer to the whole submodule



      if (fileio.is_open())
          {
          fileio << myAddr << ";" << state.first << ";" << state.second << ";" << gw1.getDByte(3) <<  ";" << gw2.getDByte(3) << "\n";
          fileio.flush();
          fileio.close();
          fileio <<std::endl;
          std::cout<< myAddr.getDByte(3) <<" closes output file!!!!" << "\n";
          }

    }

uint32_t BERGER::getRoute(const Uint128&, std::vector<Uint128>&)
{
    return 0;
}

bool BERGER::getNextHop(const Uint128&, Uint128&, int&, double&)
{
    return false;
}

void BERGER::setRefreshRoute(const Uint128&, const Uint128&, bool)
{
}

bool BERGER::isProactive()
{
    return false;
}

bool BERGER::isOurType(cPacket*)
{
    return false;
}

bool BERGER::getDestAddress(cPacket*, Uint128&)
{
    return false;
}


