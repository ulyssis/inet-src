//
// Generated file, do not edit! Created by opp_msgc 4.3 from networklayer/manetrouting/gpsr/GpsrRouteRequest.msg.
//

#ifndef _GPSRROUTEREQUEST_M_H_
#define _GPSRROUTEREQUEST_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0403
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif

// dll export symbol
#ifndef INET_API 
#  if defined(INET_EXPORT)
#    define INET_API  OPP_DLLEXPORT
#  elif defined(INET_IMPORT)
#    define INET_API  OPP_DLLIMPORT
#  else
#    define INET_API 
#  endif
#endif

// cplusplus {{
#include "IPv4Address.h"
#include "Coord.h"
// }}



/**
 * Class generated from <tt>networklayer/manetrouting/gpsr/GpsrRouteRequest.msg</tt> by opp_msgc.
 * <pre>
 * packet GpsrRouteRequest
 * {
 * 	IPv4Address src;
 * 	IPv4Address dst;
 * 	Coord srcPos;
 * 	Coord dstPos;
 * }
 * </pre>
 */
class INET_API GpsrRouteRequest : public ::cPacket
{
  protected:
    IPv4Address src_var;
    IPv4Address dst_var;
    Coord srcPos_var;
    Coord dstPos_var;

  private:
    void copy(const GpsrRouteRequest& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const GpsrRouteRequest&);

  public:
    GpsrRouteRequest(const char *name=NULL, int kind=0);
    GpsrRouteRequest(const GpsrRouteRequest& other);
    virtual ~GpsrRouteRequest();
    GpsrRouteRequest& operator=(const GpsrRouteRequest& other);
    virtual GpsrRouteRequest *dup() const {return new GpsrRouteRequest(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual IPv4Address& getSrc();
    virtual const IPv4Address& getSrc() const {return const_cast<GpsrRouteRequest*>(this)->getSrc();}
    virtual void setSrc(const IPv4Address& src);
    virtual IPv4Address& getDst();
    virtual const IPv4Address& getDst() const {return const_cast<GpsrRouteRequest*>(this)->getDst();}
    virtual void setDst(const IPv4Address& dst);
    virtual Coord& getSrcPos();
    virtual const Coord& getSrcPos() const {return const_cast<GpsrRouteRequest*>(this)->getSrcPos();}
    virtual void setSrcPos(const Coord& srcPos);
    virtual Coord& getDstPos();
    virtual const Coord& getDstPos() const {return const_cast<GpsrRouteRequest*>(this)->getDstPos();}
    virtual void setDstPos(const Coord& dstPos);
};

inline void doPacking(cCommBuffer *b, GpsrRouteRequest& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, GpsrRouteRequest& obj) {obj.parsimUnpack(b);}


#endif // _GPSRROUTEREQUEST_M_H_