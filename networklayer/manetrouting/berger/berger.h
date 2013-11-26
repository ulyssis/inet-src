#pragma once

// System includes:
#include <tr1/unordered_map>
#include <tr1/unordered_set>

// Omnet includes:
#include "omnetpp.h"

// INET includes:
#include "ManetRoutingBase.h"

// Berger includes:
#include "BergerNeighborInfo.h"
#include "Radio.h"
#include "mode.h"
#include <fstream>
#include <utility>      // std::pair, std::get

class BERGER : public ManetRoutingBase
{
	int numInitStages() const  {return 5;}
    virtual void handleMessage(cMessage *msg);
    void initialize(int stage);
    virtual uint32_t getRoute(const Uint128&, std::vector<Uint128>&);
    virtual bool getNextHop(const Uint128&, Uint128&, int&, double&);
    virtual void setRefreshRoute(const Uint128&, const Uint128&, bool);
    virtual bool isProactive();
    virtual bool isOurType(cPacket*);
    virtual bool getDestAddress(cPacket*, Uint128&);
	void doLocalBroadcast(cPacket *pk);
	void doGlobalBroadcast(cPacket *pk);
	void finish();

	protected:
		virtual void positionUpdated(double x,double y);

    public:
        typedef std::tr1::unordered_map<IPv4Address,BergerNeighborInfo*,hashIPv4Address> nh_t;

	private:
		IRoutingTable* routingTable;
		IPv4Address myAddr;
		nh_t neighborhood;
		nh_t parents, children;
        IPv4Address gw1, gw2;



		struct sdPairKey
		{
			const IPv4Address src;
			const IPv4Address dst;

			sdPairKey(const IPv4Address& src, const IPv4Address& dst) : src(src), dst(dst) {}

			bool operator==(const sdPairKey& other) const
			{
				return other.src==src && other.dst==dst;
			}
		};

		struct hashSdPairKey
		{
			size_t operator()(const sdPairKey& x) const
			{
				return x.src.getInt()*2+x.dst.getInt();
			}
		};

		struct sdPairValue
		{
			Coord srcPos;
			Coord dstPos;

			sdPairValue(Coord& srcPos, Coord& dstPos) : srcPos(srcPos),dstPos(dstPos) {}
			sdPairValue() {}
		};

		typedef std::tr1::unordered_map<sdPairKey,sdPairValue,hashSdPairKey> sdPairs_t;


		sdPairs_t sdPairs;

		struct BergerNodeInfo
		{
			const IPv4Address ip;
			const double x;
			const double y;
			const IPv4Address gw1;
			const IPv4Address gw2;
			BergerNodeInfo(const IPv4Address& ip, double x, double y, IPv4Address gw1, IPv4Address gw2) : ip(ip),x(x),y(y),gw1(gw1),gw2(gw2){}
		};


        typedef std::pair<double, double> pair_t;
		pair_t calculateLocalLinkQuality(const BergerNodeInfo& src, const BergerNodeInfo& a, const BergerNodeInfo& self, const BergerNodeInfo& b, const BergerNodeInfo& dst) const;
		pair_t state; //(delay, utility)

		friend std::ostream& operator<<(std::ostream& os, const BERGER::BergerNodeInfo& b);

		struct LLValue
		{
			IPv4Address a;
			IPv4Address b;
			double quality;

			LLValue(const IPv4Address& a,const IPv4Address& b,double quality) : a(a),b(b),quality(quality) {}
			LLValue() {quality=-1;}
		};

		typedef std::tr1::unordered_map<sdPairKey,LLValue,hashSdPairKey> ll_t;

		ll_t localLinks;

		void updateRoute(const IPv4Address& src, const IPv4Address& a, const IPv4Address& b, const IPv4Address& dst, double quality);

	public:
		typedef std::tr1::unordered_map<IPv4Address,Coord,hashIPv4Address> posTable_t;
//		void updateLocalLinks(const IPv4Address& updatedNeighbor, double nbX, double nbY);
		void updateLocalLinks(BergerNeighborInfo* bni);
		void updateLocalLinks(const BergerNodeInfo& src, const BergerNodeInfo& dst);


	private:
		static posTable_t posTable;

};

std::ostream& operator<<(std::ostream& os, const BERGER::BergerNodeInfo& b)
{
	os << b.ip << "(" << b.x << "," << b.y << b.gw1.getDByte(3) << "," <<b.gw2.getDByte(3)  <<")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const BERGER::nh_t& nh)
{
    os << "(";
    for(BERGER::nh_t::const_iterator It=nh.begin(); It!=nh.end(); ++It)
        {
        os << It->first.getDByte(3) << ",";
        }
    os <<")";
    return os;
}


